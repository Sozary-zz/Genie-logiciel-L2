#pragma once
#include "Colors.h"
#include "Component.h"

enum class INPUT_TYPE_RESTRICT { FREE, NUMBERS_ONLY, TEXT_ONLY };
class LayoutInput :public sf::Drawable, public LayoutComponent
{
public:
	LayoutInput(sf::Vector2f, sf::Vector2f, INPUT_TYPE_RESTRICT = INPUT_TYPE_RESTRICT::FREE, sf::Color = sf::Color(63, 63, 70), sf::Color = sf::Color(51, 51, 55), sf::Color = sf::Color(0, 122, 204), sf::Color = sf::Color(63, 63, 70), sf::Color = sf::Color(241, 241, 241)); // size, pos, color of the outline thickness, color of body,same with two othors param but on hovered statement, and cursor color
	virtual void update(sf::Event, std::string&);
	virtual int getComponent() const;
	virtual std::string getString() const;

private:
	sf::RectangleShape m_body;
	sf::RectangleShape m_cursor;
	sf::Color m_body_color;
	sf::Color m_body_clicked_color;
	sf::Color m_thickness_color;
	sf::Color m_thickness_clicked_color;
	sf::Color m_cursor_color;
	sf::Font m_font;
	sf::Text m_text;
	std::string m_label;
	bool m_clicked;
	bool m_hovered;
	bool m_cursor_can_be_drew;
	sf::Clock m_cursor_clock;
	sf::Vector2f m_cursor_position;
	INPUT_TYPE_RESTRICT m_type_restrict;
private:
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
};

