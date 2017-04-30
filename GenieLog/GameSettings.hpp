#pragma once
#include <SFML\Graphics.hpp>
#include "GameState.hpp"


class GameSettings: public GameState
{
public:
	GameSettings(Game* game);
	virtual void draw(const float delta_time) ;
	virtual void update(const float delta_time);
	virtual void eventLoop();



private:
	sf::View m_view;
	sf::Sprite m_background;
};

