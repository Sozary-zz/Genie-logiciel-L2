#pragma once
#include <SFML\Graphics.hpp>
#include <random>
#include <map>
#include <algorithm>
#include "GameState.hpp"
#include "TileMap.hpp"
#include "PerlinNoise.hpp"
#include "GameBattle.hpp"
#include "Menu.h"
#include "GameInventory.hpp"
#include "Parseur.hpp"

#define NB_OF_MONSTERS 5

enum class TILE_TYPE {
	BUSH,
	GRASS,
	FLOWER,
	BAD_GRASS
};

struct Map {
	TileMap tiles;
	int* movements;
	TILE_TYPE* datas;
};

struct Node {
	sf::Vector2i* position;
	int distance;
};

class GameBoard : public GameState
{
public:
	GameBoard(Game* game);
	virtual void draw(const float delta_time);
	virtual void update(const float delta_time);
	virtual void eventLoop();

	~GameBoard();

private:
	const std::vector<Entite*>& parseMonsterConfiguration() const;
	int* parseMapConfiguration(int size) const;
	void buildMap(int* build_configuration);
	bool validMap(int* map, int _x, int _y);
	bool getDistanceMap(int* _map, int _x, int _y, sf::Vector2i start) const;
	const std::vector<sf::Vector2i*> getNeigh(int* _map, int _x, int _y, sf::Vector2i *node) const;
	bool exist(const std::map<sf::Vector2i*, int>& m, sf::Vector2i* a) const;

	int getV(const std::map<sf::Vector2i*, int>& m, sf::Vector2i* a) const;
	bool blink();

	void tryToLaunchABattle(sf::Vector2i player_pos);

	bool noMonsterHere(sf::Vector2i position) const;

	static int manhattanDistance(const sf::Vector2i& a, const sf::Vector2i& b);
private:
	sf::View m_view;

	std::vector<Entite*> m_entities;
	Map* m_map;

	sf::SoundBuffer m_base_battle_sound_buffer;
	sf::Sound m_base_battle_sound;

	Sample m_collision;
	sf::Music m_main_song;
	Sample m_menu_song;

	int m_battle_issue;

	// test
	bool t_fight;
	sf::Clock t_intro;
	sf::Clock t_blink;
	bool blink_boom;
	bool t_already_started;
	int fade;

	Joueur *m_player;
	sf::Clock m_movement_clock;

	bool m_map_reloaded;

	Menu* m_menu;

	std::vector<Monstre*> m_monsters;
	sf::Vector2i  * m_monster_pos;

	Monstre* m_monster_buffer;

};

