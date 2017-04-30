#include "LayoutButton.h"
#include <iostream>
using namespace sf;
using namespace std;

LayoutButton::LayoutButton(Vector2f size, Vector2f position, Color body_color, function<void(string)> f, string label, int type, Color text_color) :
	m_function(f), m_body_color(body_color), m_label(label), m_clicked(false), m_button_type(type)
{
	m_body.setSize(size);
	m_body.setPosition(position);
	m_body.setFillColor(body_color);

	m_bottom.setSize(Vector2f(size.x, size.y*.2));
	m_bottom.setPosition(Vector2f(position.x, position.y + size.y - size.y*.2));
	m_bottom_color = Color(static_cast<int>(body_color.r)*.8, static_cast<int>(body_color.g)*.8, static_cast<int>(body_color.b)*.8);

	m_bottom.setFillColor(m_bottom_color);


	m_font.loadFromFile("data\\GOTHIC.TTF");
	m_text.setString(label);
	m_text.setFont(m_font);
	m_text.setColor(text_color);
	m_text.setCharacterSize(size.x / 6);
	m_text.setPosition(position.x + size.x / 2 - m_text.getGlobalBounds().width / 2,
		position.y + size.y / 2 - m_text.getGlobalBounds().height);
}

void LayoutButton::update(Event e, string& info)
{
	m_clicked = false;

	if (e.type == Event::TextEntered)
		if (e.key.code == 13) // press the enter it s like press the button
		{
			while (info.back() != '\n')
				info.pop_back();
			info.pop_back(); // remove this add

			m_function(info);
			info.clear();
		}


	if (e.type == Event::MouseButtonPressed)
		if (e.mouseButton.x >= m_body.getPosition().x && e.mouseButton.x < m_body.getPosition().x + m_body.getSize().x)
			if (e.mouseButton.y >= m_body.getPosition().y && e.mouseButton.y < m_body.getPosition().y + m_body.getSize().y)
			{
				m_bottom.setFillColor(m_body_color);
				m_clicked = true;
			}
	if (e.type == Event::MouseButtonReleased)
		m_bottom.setFillColor(m_bottom_color);

	if (m_clicked) // click on button for use his virtual function who do actions in consequence (maybe I have to see this again later because that s works for 1 button ONLY)
	{
		if (m_button_type == END_BUTTON_COMPONENT) {
			m_button_type = FINISH_BUTTON_STATE;
			return;
		}			
		m_function(info);
		info.clear();
	}


}

int LayoutButton::getComponent()const
{
	return m_button_type;
}

string  LayoutButton::getString() const
{
	return string("");
}

bool LayoutButton::clicked() const
{
	return m_clicked;
}

void LayoutButton::draw(RenderTarget & t, RenderStates s) const
{

	t.draw(m_body);
	t.draw(m_bottom);
	t.draw(m_text);
}
