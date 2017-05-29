#pragma once
#include <SFML\Graphics.hpp>
#include "GameState.hpp"
#include "GameSettings.hpp"
#include "GameSelector.hpp"
#include "GameCreator.hpp"
#include "ActionButton.h"


enum class BUTTON_INDEX
{
	PLAY_BUTTON,
	EDIT_BUTTON,
	SETTINGS_BUTTON,
	LOAD_BUTTON,
	QUIT_BUTTON
};
class GameMenu: public GameState
{
public:
	GameMenu(Game* game);
	virtual void draw(const float delta_time) ;
	virtual void update(const float delta_time);
	virtual void eventLoop();



private:
	sf::View m_view;
	sf::Sprite m_background;
	ActionButton** m_buttons;
	sf::Music m_menu_song;

	bool m_setSongUp;


};

