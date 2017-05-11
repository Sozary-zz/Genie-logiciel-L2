#include "GameSelector.hpp"
#include <iostream>

using namespace std;
using namespace sf;

GameSelector::GameSelector(Game * game)
{
	this->game = game;
	auto x = (Vector2f)this->game->window.getSize();

	m_view.setSize(x);
	m_view.setCenter(x*.5f);

	GameState::texture_manager->addElement("grad", "data\\gradiant.png");
	GameState::texture_manager->addElement("paladin", "data\\paladin.png");
	GameState::texture_manager->addElement("guerrier", "data\\guerrier.png");
	GameState::texture_manager->addElement("archer", "data\\archer.png");
	GameState::texture_manager->addElement("mage", "data\\mage.png");

	m_presentations = new RectangleShape[4];
	m_sprites = new Sprite[4];
	m_sprites[0].setTexture(GameState::texture_manager->getElement("paladin"));
	m_sprites[1].setTexture(GameState::texture_manager->getElement("guerrier"));
	m_sprites[2].setTexture(GameState::texture_manager->getElement("archer"));
	m_sprites[3].setTexture(GameState::texture_manager->getElement("mage"));


	for (int i = 0; i < 4; ++i)
		m_presentations[i].setTexture(&GameState::texture_manager->getElement("grad"));

	m_presentations[0].setFillColor(Color(142, 68, 173));

	m_next_button = new ActionButton("Suivant",{x.x/2-x.y/)
}

void GameSelector::draw(const float delta_time)
{
	game->window.setView(m_view);
	for (int i = 0; i < 4; ++i) {
		game->window.draw(m_presentations[0]);
		game->window.draw(m_sprites[i]);
	}

}

void GameSelector::update(const float delta_time)
{

}

void GameSelector::eventLoop()
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
