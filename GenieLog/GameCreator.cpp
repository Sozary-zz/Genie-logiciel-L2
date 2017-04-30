#include "GameCreator.hpp"
#include <iostream>

using namespace std;
using namespace sf;

GameCreator::GameCreator(Game * game) :m_quit(false)
{
	this->game = game;
	auto x = (Vector2f)this->game->window.getSize();

	m_view.setSize(x);
	m_view.setCenter(x*.5f);

	try {
		EditorChoiceBox* editor_ctxt = new EditorChoiceBox(300, 250, "Editeur");
	}
	catch (int e) {
		if (e == INTERRUPT_WINDOW_EXCEPTION)
			m_quit = true;
	}
	catch (const vector<string>& s) {
		m_height =					stoi(s[1]);
		m_width =					stoi(s[2]);
		m_number_of_monsters =		stoi(s[0]);
	}

	//m_background.setScale(x.x / m_background.getTexture()->getSize().x, x.y / m_background.getTexture()->getSize().y);
}

void GameCreator::draw(const float delta_time)
{
	game->window.setView(m_view);

	game->window.draw(m_background);

}

void GameCreator::update(const float delta_time)
{
	if (m_quit)
	{
		game->popState();
		return;
	}

}

void GameCreator::eventLoop()
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

			if (event.key.code == Keyboard::Escape) game->window.close();
			break;
		}
		default: break;
		}
	}

}
