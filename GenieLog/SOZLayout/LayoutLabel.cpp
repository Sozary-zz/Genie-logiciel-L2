#include "LayoutLabel.h"

using namespace std;
using namespace sf;

LayoutLabel::LayoutLabel(Vector2f position, string& font_path, string& label, float charac_size, Color color, Color hovered_color) :
	m_color(color), m_hovered_color(hovered_color), m_hovered(false)
{
	m_text.setString(label);
	m_text.setPosition(position);
	m_text.setCharacterSize(charac_size);

	m_font.loadFromFile(font_path);

	m_text.setFont(m_font);
	m_text.setColor(color);
}

void LayoutLabel::update(Event e, string & s)
{
	if (e.type == Event::MouseMoved)
	{
		if (m_text.getGlobalBounds().contains(Vector2f(e.mouseMove.x, e.mouseMove.y)))
		{
			m_hovered = true;
			m_text.setColor(m_hovered_color);
		}
		else
		{
			m_text.setColor(m_color);
			m_hovered = false;
		}
	}

}

int LayoutLabel::getComponent() const
{
	return LABEL_COMPONENT;
}

string LayoutLabel::getString() const
{
	return m_text.getString().toAnsiString();
}

void LayoutLabel::draw(RenderTarget & t, RenderStates s) const
{
	t.draw(m_text);
}
