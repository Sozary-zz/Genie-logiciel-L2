#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "GameState.hpp"


class GameInventory: public GameState
{
public:
	GameInventory(Game* game);
	virtual void draw(const float delta_time) ;
	virtual void update(const float delta_time);
	virtual void eventLoop();



private:
	sf::View m_view;
	sf::Sprite m_background;
	std::vector<sf::IntRect> m_items_pos;
};

