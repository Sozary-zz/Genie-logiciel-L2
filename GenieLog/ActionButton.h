#pragma once
#include <SFML\Graphics.hpp>
#include <string>


class ActionButton: public sf::Drawable, public sf::Transformable
{
public:
	ActionButton(const std::string& label, sf::Vector2f position, sf::Vector2f size, sf::Color bckgrnd, sf::Color font_color,const sf::Font &font);
	~ActionButton();

	bool buttonPushed() const;

	void update(const sf::Event& event);
	void setState(bool state);

private:
	bool m_pushed;
	bool m_hoovered;

	sf::RectangleShape m_shape;
	sf::Text m_text;

	sf::Color m_base_main_color;
	sf::Color m_base_font_color;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

