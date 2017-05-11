#include "GameSettings.hpp"
#include <iostream>

using namespace std;
using namespace sf;

GameSettings::GameSettings(Game * game)
{
	this->game = game;
	auto x = (Vector2f)this->game->window.getSize();

	m_view.setSize(x);
	m_view.setCenter(x*.5f);

	//GameState::texture_manager->addElement("settings_background", "data\\back_2.png");

//	m_background.setTexture(GameState::texture_manager->getElement("settings_background"));

	//m_background.setScale(x.x / m_background.getTexture()->getSize().x, x.y / m_background.getTexture()->getSize().y);

}

void GameSettings::draw(const float delta_time)
{
	game->window.setView(m_view);
	game->window.draw(m_background);
}

void GameSettings::update(const float delta_time)
{
	
}

void GameSettings::eventLoop()
{
	Event event;

	while (game->window.pollEvent(event))
	{
		switch (event.type)
		{
		case Event::Closed:
		{
			game->window.close();
			break;
		}

		case Event::KeyPressed:
		{
			if (event.key.code == Keyboard::A)
			{
				game->popState();
				return;
			}
				

			else	if (event.key.code == Keyboard::Escape) game->window.close();
			break;
		}
		default: break;
		}
	}

}
