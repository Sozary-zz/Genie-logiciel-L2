#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "ActionButton.h"
#include "GameState.hpp"
#include "GameBoard.hpp"
#include "PlayerNameChoiceBox.h"

class GameSelector: public GameState
{
public:
	GameSelector(Game* game,bool& end);
	virtual void draw(const float delta_time) ;
	virtual void update(const float delta_time);
	virtual void eventLoop();

private:
	sf::View m_view;

	ActionButton * m_next_button;// bouton next
	ActionButton * m_quit_button;// boutton quitter

	sf::RectangleShape * m_presentations;// rectnagles de pres
	sf::Sprite * m_sprites;// les images dedans
	sf::Text * m_text_presentation;// le text de chauque classe

	int m_selected;// la classe selec

	bool m_someone_else_selected;// cahnge curseur
	bool m_locked;// verouille choix classe

	std::string m_class;// nom classe

	sf::Music m_main_music;// musiqye

	bool& m_end;// est fini?

};

