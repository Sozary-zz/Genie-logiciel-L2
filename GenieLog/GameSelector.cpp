#include "GameSelector.hpp"
#include <iostream>

using namespace std;
using namespace sf;

GameSelector::GameSelector(Game * game) :m_selected(-1), m_someone_else_selected(false), m_locked(false)
{
	this->game = game;
	auto x = (Vector2f)this->game->window.getSize();

	m_view.setSize(x);
	m_view.setCenter(x*.5f);

	GameState::texture_manager->addElement("grad", "data\\gradiant.png");
	GameState::texture_manager->addElement("Paladin", "data\\paladin.png");
	GameState::texture_manager->addElement("Guerrier", "data\\guerrier.png");
	GameState::texture_manager->addElement("Archer", "data\\archer.png");
	GameState::texture_manager->addElement("Mage", "data\\mage.png");

	m_presentations = new RectangleShape[4];
	m_sprites = new Sprite[4];
	m_text_presentation = new Text[4];

	m_sprites[0].setTexture(GameState::texture_manager->getElement("Paladin"));
	m_sprites[1].setTexture(GameState::texture_manager->getElement("Guerrier"));
	m_sprites[2].setTexture(GameState::texture_manager->getElement("Archer"));
	m_sprites[3].setTexture(GameState::texture_manager->getElement("Mage"));


	for (int i = 0; i < 4; ++i)
	{
		m_presentations[i].setTexture(&GameState::texture_manager->getElement("grad"));
		m_presentations[i].setPosition(i*187.5 + 10 * (i + 1), 10.f);
		m_presentations[i].setSize({ 187.5,x.y / 1.5f });
		m_sprites[i].setTextureRect(IntRect(0 * TILE_SIZE, 10 * TILE_SIZE, TILE_SIZE, TILE_SIZE));
		m_sprites[i].setScale(88.5f / TILE_SIZE, 88.5f / TILE_SIZE);
		m_sprites[i].setPosition(m_presentations[i].getPosition() + Vector2f{ 10 + 88.5f / 2,10 + 88.5f / 2 });

		m_text_presentation[i].setFont(GameState::font_manager->getElement("main_font"));

		switch (i)
		{
		case 0:m_text_presentation[i].setString("Paladin"); break;
		case 1:m_text_presentation[i].setString("Guerrier"); break;
		case 2:m_text_presentation[i].setString("Archer"); break;
		case 3:m_text_presentation[i].setString("Mage"); break;

		}
		m_text_presentation[i].setCharacterSize(24.f);
		m_text_presentation[i].setPosition(m_presentations[i].getPosition() + Vector2f{ 187.5f / 2.f - m_text_presentation[i].getGlobalBounds().width / 2.f,20 + 88.5f * 3 });
	}



	m_presentations[0].setFillColor(Color(142, 68, 173));
	m_presentations[1].setFillColor(Color(41, 128, 185));
	m_presentations[2].setFillColor(Color(46, 204, 113));
	m_presentations[3].setFillColor(Color(236, 240, 241));

	m_next_button = new ActionButton("Suivant", { x.x / 4.f - (x.y / 3.5f) / 2.f,x.y - 150 }, { x.y / 3.5f, 50 }, Color::Blue, Color::White, GameState::font_manager->getElement("main_font"));
	m_quit_button = new ActionButton("Quitter", { 3 * x.x / 4.f - (x.y / 3.5f) / 2.f,x.y - 150 }, { x.y / 3.5f, 50 }, Color::Blue, Color::White, GameState::font_manager->getElement("main_font"));

}

void GameSelector::draw(const float delta_time)
{
	game->window.setView(m_view);
	for (int i = 0; i < 4; ++i) {
		game->window.draw(m_presentations[i]);
		game->window.draw(m_sprites[i]);
		game->window.draw(m_text_presentation[i]);
	}
	game->window.draw(*m_next_button);
	game->window.draw(*m_quit_button);

}

void GameSelector::update(const float delta_time)
{
	if (m_next_button->buttonPushed()) {
		try {
			PlayerNameChoiceBox* choice_ctxt = new PlayerNameChoiceBox(300, 250, "Pseudo");
		}
		catch (int e) {
			if (e == INTERRUPT_WINDOW_EXCEPTION)
				game->window.close();
		}
		catch (string& s) {
			game->pushState((GameState*)new GameBoard(this->game, m_class, s));
		}
		
	}
		

	else if (m_quit_button->buttonPushed())
		game->popState();

	if (m_someone_else_selected && !m_locked) {
		for (int i = 0; i < 4; ++i) {
			if (i != m_selected)
				m_presentations[i].setFillColor(Color(64, 64, 64, 200));
			else {
				switch (i)
				{
				case 0:m_presentations[i].setFillColor(Color(142, 68, 173)); break;
				case 1:m_presentations[i].setFillColor(Color(41, 128, 185)); break;
				case 2:	m_presentations[i].setFillColor(Color(46, 204, 113)); break;
				case 3:m_presentations[i].setFillColor(Color(236, 240, 241)); break;
				}
			}
		}

		m_someone_else_selected = false;
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

		case Event::MouseMoved: {
			for (int i = 0; i < 4; ++i)
				if (m_presentations[i].getGlobalBounds().contains({ (float)event.mouseMove.x,(float)event.mouseMove.y })) {
					m_selected = i;
					m_someone_else_selected = true;
					break;
				}
			break;
		}

		case Event::MouseButtonPressed: {

			if (event.key.code == Mouse::Left)
			{
				if (m_selected != -1) {
					m_locked = true;
					switch (m_selected)
					{
					case 0:m_class = "Paladin"; break;
					case 1:m_class = "Guerrier"; break;

					case 2:m_class = "Archer"; break;

					case 3:m_class = "Mage"; break;

					}
				}
			}
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
