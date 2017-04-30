#include "LayoutInput.h"
#include "Exception.h"
#include <iostream>

using namespace std;
using namespace sf;

LayoutInput::LayoutInput(Vector2f size, Vector2f position, INPUT_TYPE_RESTRICT type_restrict, Color outline_thickness_color, Color body_color, Color outline_thickness_cliked_color, Color body_clicked_color, Color cursor_color)
	:m_body_color(body_color), m_body_clicked_color(body_clicked_color), m_thickness_color(outline_thickness_color), m_thickness_clicked_color(outline_thickness_cliked_color), m_cursor_color(cursor_color),
	m_clicked(false), m_hovered(false), m_cursor_position(position), m_cursor_can_be_drew(false), m_type_restrict(type_restrict)
{
	m_body.setSize(size);
	m_body.setPosition(position);
	m_body.setFillColor(m_body_color);
	m_body.setOutlineThickness(1.f);
	m_body.setOutlineColor(m_thickness_color);

	m_cursor.setFillColor(cursor_color);
	m_cursor.setPosition(Vector2f(m_cursor_position.x + 3, m_cursor_position.y + size.y*.1));
	m_cursor.setSize(Vector2f(1, size.y - size.y*.3));

	m_font.loadFromFile("data\\GOTHIC.TTF");
	m_text.setFont(m_font);
	m_text.setColor(m_cursor_color);
	m_text.setCharacterSize(size.x / 8);
	m_text.setPosition(position.x + 3 - m_text.getGlobalBounds().width / 2,
		position.y + size.y*.05f - m_text.getGlobalBounds().height);

}

void LayoutInput::update(Event e, string & s)
{
	if (m_clicked)
	{

		if (e.type == Event::TextEntered)
		{
			m_body.setOutlineColor(m_thickness_clicked_color);
			if (e.key.code == 8 && m_label.size() != 0)
				m_label.pop_back();

			else if (e.key.code < 128 && e.key.code != 13)// hight charac and ENTER key
				if (!(m_label.size() == 0 && e.key.code == 8))
					if (m_text.getGlobalBounds().width + m_text.getCharacterSize() < m_body.getSize().x)
					{
						m_label.push_back((char)e.key.code);
						string copy_for_iss = m_label;
						switch (m_type_restrict)
						{
						case INPUT_TYPE_RESTRICT::FREE:
							break;
						case INPUT_TYPE_RESTRICT::NUMBERS_ONLY:
							if (!Exception::isNumber(copy_for_iss) || e.key.code==32) // only numbers entred? And no space!
							{
								m_label.pop_back(); // no, we delete it now
								m_body.setOutlineColor(Color::Red);
							}

							break;
						case INPUT_TYPE_RESTRICT::TEXT_ONLY: // same for text
							if (!Exception::isPureString(m_label))
							{
								m_label.pop_back();
								m_body.setOutlineColor(Color::Red);
							}

							break;
						default:
							break;
						}

					}


		}

		m_text.setString(m_label);
		m_cursor.setPosition(Vector2f(m_cursor_position.x + 3 + m_text.getGlobalBounds().width, m_cursor_position.y + m_body.getSize().y*.1));

	}


	if (!m_clicked) // not clicked, otherwise if mouse left the area, the colors are restored 
		if (e.type == Event::MouseMoved)
		{
			if (m_body.getGlobalBounds().contains(Vector2f(e.mouseMove.x, e.mouseMove.y)))
			{
				m_hovered = true;
				m_body.setOutlineColor(m_thickness_clicked_color);
			}
			else
			{
				m_body.setOutlineColor(m_thickness_color);
				m_hovered = false;
			}
		}

	if (e.type == Event::MouseButtonPressed)
	{
		if (m_body.getGlobalBounds().contains(Vector2f(e.mouseButton.x, e.mouseButton.y)))
		{
			m_clicked = true;
			m_body.setFillColor(m_body_clicked_color);
			m_body.setOutlineColor(m_thickness_clicked_color);
			m_cursor_can_be_drew = true;
			m_cursor_clock.restart();
		}
		else
		{
			m_cursor_can_be_drew = false;
			m_clicked = false;
			m_body.setFillColor(m_body_color);
			m_body.setOutlineColor(m_thickness_color);
		}
	}



}

int LayoutInput::getComponent()const
{
	return INPUT_COMPONENT;
}

string LayoutInput::getString() const
{
	return m_label;
}

void LayoutInput::draw(RenderTarget & t, RenderStates s) const
{
	t.draw(m_body);
	if (m_cursor_can_be_drew)
		t.draw(m_cursor);
	t.draw(m_text);
}
