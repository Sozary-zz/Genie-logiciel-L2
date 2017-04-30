#pragma once
#include <functional>
#include "Colors.h"
#include "Component.h"

class LayoutButton :public sf::Drawable, public LayoutComponent
{
public:
	LayoutButton(sf::Vector2f, sf::Vector2f, sf::Color, std::function<void(std::string)>, std::string, int = BUTTON_COMPONENT, sf::Color = sf::Color(0, 0, 0));
	virtual void update(sf::Event, std::string&);
	virtual int getComponent() const;
	virtual std::string getString() const;
	bool clicked() const;

private:
	sf::RectangleShape m_body;
	sf::RectangleShape m_bottom;
	sf::Color m_body_color;
	sf::Color m_bottom_color;
	sf::Color m_clicked_color;
	sf::Color m_clicked_bottom_color;
	std::function<void(std::string)> m_function;
	std::string m_label;
	sf::Font m_font;
	sf::Text m_text;
	bool m_clicked;
	int m_button_type;
private:
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

};

