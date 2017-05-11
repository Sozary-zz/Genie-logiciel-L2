#include "GameBoard.hpp"
#include <iostream>

using namespace std;
using namespace sf;


// https://downloads.khinsider.com/game-soundtracks/album/pokemon-ruby-sapphire-music-super-complete
GameBoard::GameBoard(Game * game) :
	m_monster_buffer(nullptr), t_fight(false), t_already_started(false), m_just_left_a_battle(false)
{

	m_base_battle_sound_buffer.loadFromFile("data\\songs\\009_Battle_Wild_Pok_mon_.ogg");
	m_base_battle_sound.setBuffer(m_base_battle_sound_buffer);

	m_collision.load("data\\songs\\sounds_effect\\emerald_0003_collision.wav");
	m_collision.sample.setVolume(1);
	m_collision.running = false;

	m_main_song.openFromFile("data\\songs\\048_Route_111.ogg");
	m_main_song.setLoop(true);
	m_main_song.setVolume(1);
	m_main_song.play();


	m_menu_song.load("data\\songs\\sounds_effect\\emerald_00F8_menu.wav");
	m_menu_song.running = false;
	m_menu_song.sample.setVolume(1);

	m_base_battle_sound.setLoop(true);	m_base_battle_sound.setVolume(1);
	//m_player = new Joueur("Rayquaza", "Player", 100, 0, 5, 1);

	m_player = ChargerJoueur("Loan", "Paladin");
	if (m_player == NULL)
		game->window.close();
	m_monster_pos = new Vector2i[NB_OF_MONSTERS];

	int monster_compt;

	this->game = game;
	auto x = (Vector2f)this->game->window.getSize();

	m_view.setSize(x);
	m_view.setCenter(x*.5f);

	m_map = new Map;

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<>dis(0, 9999);

	int* level = new int[DEFAULT_HEIGHT*DEFAULT_WIDTH];

	m_map->movements = new int[DEFAULT_HEIGHT*DEFAULT_WIDTH];
	m_map->datas = new TILE_TYPE[DEFAULT_HEIGHT*DEFAULT_WIDTH];


	do {
		monster_compt = 0;
		auto pn = PerlinNoise(dis(gen));

		for (int x = 0; x < DEFAULT_WIDTH; ++x)
			for (int y = 0; y < DEFAULT_HEIGHT; ++y) {
				double n = 10 * pn.noise(x, y, 2.6);

				/*	if (n < 4 && dis(gen) < 5000)
						level[x + y*DEFAULT_HEIGHT] = (int)TILE_TYPE::BAD_GRASS;
					else */
				if (n < 4.5)
					level[x + y*DEFAULT_HEIGHT] = (int)TILE_TYPE::FLOWER;
				else if (n < 5.5)
					level[x + y*DEFAULT_HEIGHT] = (int)TILE_TYPE::GRASS;
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

	auto where_can_I_pose = availablePositions(m_map->datas);

	auto rand_player_pos = dis(gen);
	Vector2i player_pos = where_can_I_pose[rand_player_pos%where_can_I_pose.size()];
	where_can_I_pose.erase(where_can_I_pose.begin() + rand_player_pos%where_can_I_pose.size());

	for (int i = 0; i < NB_OF_MONSTERS; ++i)
	{
		auto rand_monster_pos = dis(gen);
		Vector2i monster_pos = where_can_I_pose[rand_monster_pos%where_can_I_pose.size()];
		where_can_I_pose.erase(where_can_I_pose.begin() + rand_monster_pos%where_can_I_pose.size());

		auto rand = dis(gen);
		DIRECTION or ;
		if (rand <= 2500)
			or = UP;
		else if (rand > 2500 && rand <= 5000)
			or = DOWN;
		else if (rand > 2500 && rand <= 5000)
			or = LEFT;
		else
			or = RIGHT;

		m_monsters.push_back(ChargerMonstre("Gobelins"));
		m_monsters.back()->adjustPos({ monster_pos.y,monster_pos.x },
			Vector2i{ 100 + monster_pos.y*(int)(m_map->tiles.getScale().x * 16) ,75 + monster_pos.x*(int)(m_map->tiles.getScale().y * 16) },
			Vector2f{ (m_map->tiles.getScale().x * 16) / 32.f  ,(m_map->tiles.getScale().y * 16) / 32.f }, or );
	}



	m_player->adjustPos({ player_pos.y,player_pos.x }, Vector2i{ 100 + player_pos.y*(int)(m_map->tiles.getScale().x * 16) ,75 + player_pos.x*(int)(m_map->tiles.getScale().y * 16) },
		Vector2f{ (m_map->tiles.getScale().x * 16) / TILE_SIZE  ,(m_map->tiles.getScale().y * 16) / TILE_SIZE },
		Vector2f{ m_map->tiles.getScale().x * 16, m_map->tiles.getScale().y * 16
	});

	m_menu = new Menu;
	m_menu->adjustPos({ 175,200 }, { 520,79 });
	m_menu->setVisible(false);
	m_movement_clock.restart();

	tryToLaunchABattle(m_player->positionInGrid());

}

void GameBoard::draw(const float delta_time)
{
	game->window.setView(m_view);
	game->window.draw(m_map->tiles);
	game->window.draw(*m_player);

	for (auto&x : m_monsters)
		game->window.draw(*x);

	if (m_menu->isVisible())
		game->window.draw(*m_menu);


}

void GameBoard::update(const float delta_time)
{

	m_collision.update();
	m_menu_song.update();

	if (m_just_left_a_battle)
	{
		m_main_song.setVolume(1);


		tryToLaunchABattle(m_player->positionInGrid());
		m_just_left_a_battle = false;
	}

	if (t_fight)
		blink();
}

void GameBoard::eventLoop()
{

	Event event;
	Time frame_time = m_movement_clock.restart();
	if (!m_player->isRunning())
	{
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
				if (t_fight)break;
				if (event.key.code == Keyboard::A)
				{
					game->popState();
					return;
				}
				else	if (event.key.code == Keyboard::Escape)
					game->window.close();
				else if (event.key.code == Keyboard::Return)
				{
					if (m_menu->isVisible()) {
						switch (m_menu->getChoice())
						{
						case CHOICE::QUIT:
							m_menu->setVisible(false);
							break;
						case CHOICE::INVENTORY:
							//	cout << "inventaire" << endl;
							game->pushState((GameState*)new GameInventory(this->game));
							return;
							break;

						case CHOICE::SAVE:
							cout << "sauvegarde" << endl;

							break;

						case CHOICE::PROFIL:
							cout << "profil" << endl;
							break;
						}

					}
					else {
						m_menu->setVisible(true);
						if (!m_menu_song.running)
							m_menu_song.run();
					}
				}

				else if (event.key.code == Keyboard::Left) {
					if (m_menu->isVisible())
						break;
					if (m_map->datas[m_player->positionInGrid().x - 1 + m_player->positionInGrid().y*DEFAULT_HEIGHT] != TILE_TYPE::BUSH
						&&  m_map->datas[m_player->positionInGrid().x - 1 + m_player->positionInGrid().y*DEFAULT_HEIGHT] != TILE_TYPE::BAD_GRASS && m_player->positionInGrid().x > 0)
					{
						m_player->left();
						tryToLaunchABattle(m_player->positionInGrid());
						return;
					}
					else
					{
						m_player->_left_();
						if (!m_collision.running)
							m_collision.run();


					}

				}
				else if (event.key.code == Keyboard::Right) {
					if (m_menu->isVisible())
						break;
					if (m_player->positionInGrid().x < DEFAULT_WIDTH - 1 && m_map->datas[m_player->positionInGrid().x + 1 + m_player->positionInGrid().y*DEFAULT_HEIGHT] != TILE_TYPE::BUSH
						&&  m_map->datas[m_player->positionInGrid().x + 1 + m_player->positionInGrid().y*DEFAULT_HEIGHT] != TILE_TYPE::BAD_GRASS)
					{
						m_player->right();
						tryToLaunchABattle(m_player->positionInGrid());
						return;
					}
					else
					{
						m_player->_right_();
						if (!m_collision.running)
							m_collision.run();


					}

				}
				else if (event.key.code == Keyboard::Up) {
					if (m_menu->isVisible())
						m_menu->up();

					else {
						if (m_map->datas[m_player->positionInGrid().x + (m_player->positionInGrid().y - 1)*DEFAULT_HEIGHT] != TILE_TYPE::BUSH
							&&  m_map->datas[m_player->positionInGrid().x + (m_player->positionInGrid().y - 1)*DEFAULT_HEIGHT] != TILE_TYPE::BAD_GRASS && m_player->positionInGrid().y > 0)
						{
							m_player->up();
							tryToLaunchABattle(m_player->positionInGrid());
							return;
						}
						else
						{
							m_player->_up_();
							if (!m_collision.running)
								m_collision.run();

						}
					}


				}
				else if (event.key.code == Keyboard::Down) {
					if (m_menu->isVisible())
						m_menu->down();
					else {
						if (m_player->positionInGrid().y < DEFAULT_HEIGHT - 1 && m_map->datas[m_player->positionInGrid().x + (m_player->positionInGrid().y + 1)*DEFAULT_HEIGHT] != TILE_TYPE::BUSH
							&&  m_map->datas[m_player->positionInGrid().x + (m_player->positionInGrid().y + 1)*DEFAULT_HEIGHT] != TILE_TYPE::BAD_GRASS)
						{
							m_player->down();
							tryToLaunchABattle(m_player->positionInGrid());
							return;
						}
						else
						{
							m_player->_down_();
							if (!m_collision.running)
								m_collision.run();
						}
					}


				}
				break;
			}

			}
		}
	}
	else
	{
		while (game->window.pollEvent(event));
		m_player->continueAnim(frame_time);
	}






}

GameBoard::~GameBoard()
{
	m_main_song.stop();
	m_collision.sample.stop();
	m_menu_song.sample.stop();
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

std::vector<sf::Vector2i> GameBoard::availablePositions(TILE_TYPE* map) const
{
	vector<Vector2i> res;
	for (int x = 0; x < DEFAULT_WIDTH; ++x)
		for (int y = 0; y < DEFAULT_HEIGHT; ++y)
			if ((int)m_map->datas[y + x*DEFAULT_HEIGHT] != 0)
				res.push_back({ x,y });

	return res;
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
		m_main_song.setVolume(0);
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
		t_already_started = false;
		t_fight = false;
		game->pushState((GameState*)new GameBattle(this->game, m_player, m_monster_buffer, &m_battle_issue, &m_monsters));
		m_just_left_a_battle = true;
		m_map->tiles.fade(Color(255, 255, 255));
		m_base_battle_sound.stop();


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

void GameBoard::tryToLaunchABattle(sf::Vector2i player_pos)
{
	for (auto&x : m_monsters)
		if (x->recupPos() == (player_pos + Vector2i(1, 0)) ||
			x->recupPos() == (player_pos + Vector2i(-1, 0)) ||
			x->recupPos() == (player_pos + Vector2i(0, 1)) ||
			x->recupPos() == (player_pos + Vector2i(0, -1))) {

			m_monster_buffer = x;
			t_fight = true;
			return;
		}
}

bool GameBoard::noMonsterHere(sf::Vector2i position) const
{
	for (int i = 0; i < NB_OF_MONSTERS; ++i)
		if (position == m_monster_pos[i])
			return false;
	return true;
}

int GameBoard::manhattanDistance(const sf::Vector2i & a, const sf::Vector2i & b)
{
	return abs(a.x - b.x) + abs(a.y - b.y);
}

