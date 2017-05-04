#pragma once
#include <SFML\Graphics.hpp>
#include "GameState.hpp"

class Menu: public sf::Drawable
{
public:
	Menu();
	~Menu();

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Sprite m_bckd;
};

