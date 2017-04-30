#pragma once
#include "Colors.h"
#include "Component.h"


class LayoutLabel :public sf::Drawable, public LayoutComponent
{
public:
	LayoutLabel(sf::Vector2f, std::string&, std::string&, float, sf::Color = sf::Color(0, 0, 0), sf::Color = sf::Color(0, 0, 0));
	// pos, font path, text,charac size, normal color, hovered color
	virtual void update(sf::Event, std::string&);
	virtual int getComponent() const;
	virtual std::string getString() const;

private:
	sf::Text m_text;
	sf::Font m_font;
	sf::Color m_color;
	sf::Color m_hovered_color;
	bool m_hovered;

private:
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
};


