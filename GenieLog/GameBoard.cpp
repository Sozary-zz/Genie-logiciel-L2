#include "GameBoard.hpp"
#include <iostream>

using namespace std;
using namespace sf;


// https://downloads.khinsider.com/game-soundtracks/album/pokemon-ruby-sapphire-music-super-complete
GameBoard::GameBoard(Game * game)
{
	m_base_battle_sound_buffer.loadFromFile("data\\songs\\009_Battle_Wild_Pok_mon_.ogg");
	m_base_battle_sound.setBuffer(m_base_battle_sound_buffer);
	m_base_battle_sound.setLoop(true);	m_base_battle_sound.setVolume(1);
	m_player = new Joueur("Rayquaza", 100, 0, 5, 1);
	this->game = game;
	auto x = (Vector2f)this->game->window.getSize();

	m_view.setSize(x);
	m_view.setCenter(x*.5f);

	//	m_background.setScale(x.x / m_background.getTexture()->getSize().x, x.y / m_background.getTexture()->getSize().y);

	m_map = new Map;

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<>dis(0, 9999);

	int* level = new int[DEFAULT_HEIGHT*DEFAULT_WIDTH];

	m_map->movements = new int[DEFAULT_HEIGHT*DEFAULT_WIDTH];
	m_map->datas = new TILE_TYPE[DEFAULT_HEIGHT*DEFAULT_WIDTH];

	Vector2i available_pos = { -1,-1 };

	do {
		auto pn = PerlinNoise(dis(gen));
		for (int x = 0; x < DEFAULT_WIDTH; ++x)
			for (int y = 0; y < DEFAULT_HEIGHT; ++y) {
				double n = 10 * pn.noise(x, y, 2.6);

				if (n < 4 && dis(gen) < 5000)
					level[x + y*DEFAULT_HEIGHT] = (int)TILE_TYPE::BAD_GRASS;
				else if (n < 4.5)
					level[x + y*DEFAULT_HEIGHT] = (int)TILE_TYPE::FLOWER;
				else if (n < 5.5)
				{
					level[x + y*DEFAULT_HEIGHT] = (int)TILE_TYPE::GRASS;
					if (available_pos.x == -1 && available_pos.y == -1)
						available_pos = { x,y };

				}

				else if (n < 6.5)
					level[x + y*DEFAULT_HEIGHT] = (int)TILE_TYPE::BUSH;
				else
					level[x + y*DEFAULT_HEIGHT] = (int)TILE_TYPE::GRASS;

				m_map->datas[x + y*DEFAULT_HEIGHT] = (TILE_TYPE)level[x + y*DEFAULT_HEIGHT];

			}
	} while (!validMap((int*)m_map->datas, DEFAULT_WIDTH, DEFAULT_HEIGHT));



	m_map->tiles.load("data\\tileset.png", Vector2u(16, 16), level, DEFAULT_WIDTH, DEFAULT_HEIGHT);
	m_map->tiles.setScale((x.x - 200) / (16 * DEFAULT_WIDTH), (x.y - 150) / (16 * DEFAULT_HEIGHT));
	m_map->tiles.move(100, 75);

	t_fight = true;
	t_already_started = false;

	m_player->adjustPos(Vector2i{ 100 + available_pos.x*(int)(m_map->tiles.getScale().x * 16) ,75 + available_pos.y*(int)(m_map->tiles.getScale().y * 16) },
		Vector2f{ (m_map->tiles.getScale().x * 16) / TILE_SIZE  ,(m_map->tiles.getScale().y * 16) / TILE_SIZE });


}

void GameBoard::draw(const float delta_time)
{
	game->window.setView(m_view);
	game->window.draw(m_map->tiles);
	game->window.draw(*m_player);
}

void GameBoard::update(const float delta_time)
{
	/*	if (t_fight)
			blink();*/
}

void GameBoard::eventLoop()
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
			else if (event.key.code == Keyboard::Left) {

			}
			break;
		}
		default: break;
		}
	}

}

GameBoard::~GameBoard()
{
	delete m_map;

	for (auto&x : m_entities)
		delete x;
}

const vector<Entite*>& GameBoard::parseMonsterConfiguration() const
{
	return vector<Entite*>();
}

int * GameBoard::parseMapConfiguration(int size) const
{
	return nullptr;
}

void GameBoard::buildMap(int * build_configuration)
{
}

bool GameBoard::validMap(int * map, int _x, int _y)
{
	Vector2i start;
	bool _continue = true;

	for (int x = 0; x < _x; ++x)
	{
		if (!_continue)break;
		for (int y = 0; y < _y; ++y)
		{
			if (!_continue)break;

			if (map[y + x*DEFAULT_HEIGHT] != (int)TILE_TYPE::BUSH && map[y + x*DEFAULT_HEIGHT] != (int)TILE_TYPE::BAD_GRASS)
			{
				start = { x,y };
				_continue = false;
			}
		}

	}

	return getDistanceMap(map, _x, _y, start);
}

bool GameBoard::getDistanceMap(int* _map, int _x, int _y, Vector2i start) const
{
	map<Vector2i*, int> distance;
	vector<Vector2i*> frontier;

	frontier.push_back(&start);
	distance[&start] = 0;

	while (!frontier.empty()) {
		auto current = frontier.front();
		vector<Vector2i*> neigh = getNeigh(_map, _x, _y, current);
		for (auto &x : neigh)
			if (!exist(distance, x))
			{
				frontier.push_back(x);
				distance[x] = 1 + distance[current];
			}

		frontier.erase(frontier.begin());
	}

	for (int x = 0; x < _x; ++x)
		for (int y = 0; y < _y; ++y)
			if (_map[y + x*DEFAULT_HEIGHT] != (int)TILE_TYPE::BUSH && _map[y + x*DEFAULT_HEIGHT] != (int)TILE_TYPE::BAD_GRASS && getV(distance, new Vector2i(y, x)) == -1)
				return false;

	return  true;
}

const vector<Vector2i*> GameBoard::getNeigh(int * _map, int _x, int _y, Vector2i* node) const
{
	vector<Vector2i*> res;

	if (node->x + 1 < _x && _map[(node->x + 1) + (node->y)*DEFAULT_HEIGHT] != (int)TILE_TYPE::BUSH  &&  _map[(node->x + 1) + (node->y)*DEFAULT_HEIGHT] != (int)TILE_TYPE::BAD_GRASS)
		res.push_back(new Vector2i{ node->x + 1,node->y });

	if (node->x - 1 >= 0 && _map[(node->x - 1) + (node->y)*DEFAULT_HEIGHT] != (int)TILE_TYPE::BUSH &&  _map[(node->x + 1) + (node->y)*DEFAULT_HEIGHT] != (int)TILE_TYPE::BAD_GRASS)
		res.push_back(new Vector2i{ node->x - 1,node->y });

	if (node->y + 1 < _y && _map[(node->x) + (node->y + 1)*DEFAULT_HEIGHT] != (int)TILE_TYPE::BUSH &&  _map[(node->x + 1) + (node->y)*DEFAULT_HEIGHT] != (int)TILE_TYPE::BAD_GRASS)
		res.push_back(new Vector2i{ node->x,node->y + 1 });

	if (node->y - 1 >= 0 && _map[(node->x) + (node->y - 1)*DEFAULT_HEIGHT] != (int)TILE_TYPE::BUSH  &&  _map[(node->x + 1) + (node->y)*DEFAULT_HEIGHT] != (int)TILE_TYPE::BAD_GRASS)
		res.push_back(new Vector2i{ node->x,node->y - 1 });

	return res;
}

bool GameBoard::exist(const map<Vector2i*, int>& m, Vector2i * a) const
{
	for (auto&x : m)
		if (*x.first == *a)
			return true;
	return false;
}

int GameBoard::getV(const std::map<sf::Vector2i*, int>& m, sf::Vector2i* a) const
{
	for (auto&x : m)
		if (*x.first == *a)
			return x.second;
	return -1;
}

bool GameBoard::blink()
{
	if (!t_already_started) {
		t_intro.restart(); m_base_battle_sound.setPlayingOffset(seconds(.2f));
		m_base_battle_sound.play();
		t_already_started = true;

		t_blink.restart();
		blink_boom = false;
		m_map->tiles.fade(Color(64, 64, 64));
	}
	if (t_intro.getElapsedTime().asSeconds() >= 1.2f && t_intro.getElapsedTime().asSeconds() < 2.6f) {

		m_map->tiles.fade(Color(fade, fade, fade));
		fade = (1 - (t_intro.getElapsedTime().asSeconds() / 1.3f))*255.f;
	}
	else if (t_intro.getElapsedTime().asSeconds() >= 2.6f)
	{
		t_fight = false;
		game->pushState((GameState*)new GameBattle(this->game, m_player, new Monstre("Kyogre", 50, 0, 2, 0), &m_battle_issue));
		m_map->tiles.fade(Color(255, 255, 255));
		m_base_battle_sound.stop();
		return true;
	}
	else {

		if (t_blink.getElapsedTime().asSeconds() >= .1f)
		{
			if (!blink_boom)
			{
				m_map->tiles.fade(Color(255, 255, 255));
				blink_boom = true;
			}

			else
			{
				blink_boom = false;
				m_map->tiles.fade(Color(64, 64, 64));
			}

			t_blink.restart();
		}


	}
	return false;
}

int GameBoard::manhattanDistance(const sf::Vector2i & a, const sf::Vector2i & b)
{
	return abs(a.x - b.x) + abs(a.y - b.y);
}

