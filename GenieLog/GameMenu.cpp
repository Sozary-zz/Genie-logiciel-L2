#include "GameMenu.hpp"
#include <iostream>

using namespace std;
using namespace sf;

GameMenu::GameMenu(Game * game):m_setSongUp(false)
{
	this->game = game;
	auto x = (Vector2f)this->game->window.getSize();

	m_view.setSize(x);
	m_view.setCenter(x*.5f);

	GameState::texture_manager->addElement("menu_background", "data\\back.png");
	GameState::font_manager->addElement("main_font", "data\\VCR_OSD_MONO_1.001.ttf");

	m_background.setTexture(GameState::texture_manager->getElement("menu_background"));

	m_background.setScale(x.x / m_background.getTexture()->getSize().x, x.y / m_background.getTexture()->getSize().y);

	m_buttons = new ActionButton*[5];

	m_buttons[static_cast<int>(BUTTON_INDEX::PLAY_BUTTON)] = new ActionButton("Jouer", Vector2f(x.x / 2 - 250 / 2.f, (x.y / 7.f) * 1), Vector2f(250, 50), Color(0,140,186), Color::White, GameState::font_manager->getElement("main_font"));
	m_buttons[static_cast<int>(BUTTON_INDEX::LOAD_BUTTON)] = new ActionButton("Charger", Vector2f(x.x / 2 - 250 / 2.f, (x.y / 7.f) * 2), Vector2f(250, 50), Color(0, 140, 186), Color::White, GameState::font_manager->getElement("main_font"));
	m_buttons[static_cast<int>(BUTTON_INDEX::EDIT_BUTTON)] = new ActionButton("Éditeur de carte", Vector2f(x.x / 2 - 250 / 2.f, (x.y / 7.f) * 3), Vector2f(250, 50), Color(0, 140, 186), Color::White, GameState::font_manager->getElement("main_font"));
	m_buttons[static_cast<int>(BUTTON_INDEX::SETTINGS_BUTTON)] = new ActionButton("Réglages", Vector2f(x.x / 2 - 250 / 2.f, (x.y / 7.f) * 4), Vector2f(250, 50), Color(0, 140, 186), Color::White, GameState::font_manager->getElement("main_font"));
	m_buttons[static_cast<int>(BUTTON_INDEX::QUIT_BUTTON)] = new ActionButton("Quitter", Vector2f(x.x / 2 - 250 / 2.f, (x.y / 7.f) * 6), Vector2f(250, 50), Color(0, 140, 186), Color::White, GameState::font_manager->getElement("main_font"));

	m_menu_song.openFromFile("data\\songs\\003_Title_Screen_Main_Theme.ogg");
	m_menu_song.setLoop(true);
	m_menu_song.setVolume(MAIN_VOLUME);
	m_menu_song.play();

}

void GameMenu::draw(const float delta_time)
{
	game->window.setView(m_view);

	game->window.draw(m_background);
	for (int i = 0; i < 5; ++i)
		game->window.draw(*m_buttons[i]);
}

void GameMenu::update(const float delta_time)
{
	if (m_setSongUp) {
		m_menu_song.setVolume(MAIN_VOLUME);
		m_setSongUp = false;
	}		

	for (int i = 0; i < 5; ++i)
	{
		if (m_buttons[i]->buttonPushed())
		{
			switch (i)
			{
			case (int)BUTTON_INDEX::QUIT_BUTTON:
		

				game->window.close();

			case (int)BUTTON_INDEX::SETTINGS_BUTTON:
				break;
				/*game->pushState((GameState*)new GameSettings(this->game));
				m_buttons[i]->setState(false);
				break;*/

			case (int)BUTTON_INDEX::PLAY_BUTTON:
				m_menu_song.setVolume(0);
				game->pushState((GameState*)new GameSelector(this->game, m_setSongUp));
				m_buttons[i]->setState(false);
				break;

		case (int)BUTTON_INDEX::EDIT_BUTTON:
			break;
				/*game->pushState((GameState*)new GameCreator(this->game));
				m_buttons[i]->setState(false);
				break;*/
			}
		}
	}

}

void GameMenu::eventLoop()
{
	Event event;

	while (game->window.pollEvent(event))
	{
		for (int i = 0; i < 5; ++i)
			m_buttons[i]->update(event);

		switch (event.type)
		{
		case Event::Closed:
		{
			game->window.close();
			break;
		}

		case Event::KeyPressed:
		{

			if (event.key.code == Keyboard::Escape) game->window.close();
			break;
		}
		default: break;
		}
	}

}


