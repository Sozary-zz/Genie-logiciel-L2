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
	{
		m_presentations[i].setTexture(&GameState::texture_manager->getElement("grad"));
		m_presentations[i].setPosition(i*187.5 + 10*(i+1), 10.f);
		m_presentations[i].setSize({187.5,x.y/1.5f});
	}

	m_presentations[0].setFillColor(Color(142, 68, 173));
	m_presentations[1].setFillColor(Color(41,128,185));
	m_presentations[2].setFillColor(Color(46,204,113));
	m_presentations[3].setFillColor(Color(236,240,241));

	m_next_button = new ActionButton("Suivant", { x.x/4.f- (x.y / 3.5f)/2.f,x.y-150 }, { x.y/3.5f, 50 }, Color::Blue, Color::White, GameState::font_manager->getElement("main_font"));
	m_quit_button = new ActionButton("Quitter", { 3*x.x / 4.f - (x.y / 3.5f) / 2.f,x.y - 150 }, { x.y / 3.5f, 50 }, Color::Blue, Color::White, GameState::font_manager->getElement("main_font"));

}

void GameSelector::draw(const float delta_time)
{
	game->window.setView(m_view);
	for (int i = 0; i < 4; ++i) {
		game->window.draw(m_presentations[i]);
		//game->window.draw(m_sprites[i]);
	}
	game->window.draw(*m_next_button);
	game->window.draw(*m_quit_button);

}

void GameSelector::update(const float delta_time)
{
	if (m_next_button->buttonPushed()) {
		game->popState();
		game->pushState((GameState*)new GameBoard(this->game));

	}
	else if (m_quit_button->buttonPushed()) {
		game->popState();

	}
}

void GameSelector::eventLoop()
{
	Event event;

	while (game->window.pollEvent(event))
	{
		m_next_button->update(event);
		m_quit_button->update(event);
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
