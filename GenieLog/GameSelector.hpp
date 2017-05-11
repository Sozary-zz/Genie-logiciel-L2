#pragma once
#include <SFML\Graphics.hpp>
#include "ActionButton.h"
#include "GameState.hpp"
#include "GameBoard.hpp"

class GameSelector: public GameState
{
public:
	GameSelector(Game* game);
	virtual void draw(const float delta_time) ;
	virtual void update(const float delta_time);
	virtual void eventLoop();

private:
	sf::View m_view;

	ActionButton * m_next_button;
	ActionButton * m_quit_button;

	sf::RectangleShape * m_presentations;
	sf::Sprite * m_sprites;
	sf::Text * m_text_presentation;

	int m_selected;

	bool m_someone_else_selected;
	bool m_locked;

	std::string m_class;

};

