#pragma once
#include <SFML\Graphics.hpp>
#include "GameState.hpp"
#include "EditorChoiceBox.h"


class GameCreator: public GameState
{
public:
	GameCreator(Game* game);
	virtual void draw(const float delta_time) ;
	virtual void update(const float delta_time);
	virtual void eventLoop();

private:
	bool m_quit;
	sf::View m_view;
	sf::Sprite m_background;

	int m_height;
	int m_width;
	int m_number_of_monsters;
};

