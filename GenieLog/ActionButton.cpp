#include "ActionButton.h"

using namespace sf;
using namespace std;

ActionButton::ActionButton(const string & label, Vector2f position, Vector2f size, Color bckgrnd, Color font_color, const Font & font)
	:m_pushed(false), m_hoovered(false), m_base_font_color(font_color), m_base_main_color(bckgrnd)
{
	m_text.setString(label);
	m_text.setFont(font);
	m_text.setColor(font_color);
	m_text.setCharacterSize(size.y*0.5f);
	m_text.setPosition(position+Vector2f(size.x/2.f-m_text.getGlobalBounds().width/2.f, size.y / 2.f - m_text.getGlobalBounds().height ));

	m_shape.setFillColor(bckgrnd);
	m_shape.setSize(size);
	m_shape.setPosition(position);
}

ActionButton::~ActionButton()
{
}

bool ActionButton::buttonPushed() const
{
	return m_pushed;
}

void ActionButton::update(const Event & event)
{
	m_pushed = false;

	if (m_shape.getGlobalBounds().contains(Vector2f(event.mouseButton.x, event.mouseButton.y))
		&& event.type == Event::MouseButtonPressed)
		m_pushed = true;

	if (m_shape.getGlobalBounds().contains(Vector2f(event.mouseMove.x, event.mouseMove.y))
		&& event.type == Event::MouseMoved)
		m_hoovered = true;
	else
		m_hoovered = false;

	if (m_hoovered) {
		if (m_shape.getFillColor().toInteger() == m_base_main_color.toInteger())
			m_shape.setFillColor(Color(0, 102, 135));
	}

	else
		if (m_shape.getFillColor().toInteger() != m_base_main_color.toInteger())
			m_shape.setFillColor(m_base_main_color);
}

void ActionButton::setState(bool state)
{
	m_pushed = state;
}

void ActionButton::draw(RenderTarget & target, RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_shape);
	target.draw(m_text);
}

