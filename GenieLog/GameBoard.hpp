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



enum class TILE_TYPE { // type de tile
	BUSH,
	GRASS,
	FLOWER,
	BAD_GRASS
};

struct Map { // une carte avec ses tiles, où on peut passer et ou sont les monstres
	TileMap tiles;
	int* movements;
	TILE_TYPE* datas;
};

struct Node {// un noeud avec une position et une distance du point central
	sf::Vector2i* position;
	int distance;
};

class GameBoard : public GameState
{
public:
	GameBoard(Game* game,std::string& classe, std::vector<std::string>& infos);
	virtual void draw(const float delta_time);
	virtual void update(const float delta_time);
	virtual void eventLoop();

	~GameBoard();

private:
	const std::vector<Entite*>& parseMonsterConfiguration() const;// recupere infos monstre
	int* parseMapConfiguration(int size) const;// recupere infos player
	void buildMap(int* build_configuration);//genere carte
	bool validMap(int* map, int _x, int _y);// carte valide?
	bool getDistanceMap(int* _map, int _x, int _y, sf::Vector2i start) const; // distance valide?
	const std::vector<sf::Vector2i*> getNeigh(int* _map, int _x, int _y, sf::Vector2i *node) const;// recup voisin noeud carte
	bool exist(const std::map<sf::Vector2i*, int>& m, sf::Vector2i* a) const; // node dans vector?

	std::vector<sf::Vector2i> availablePositions(TILE_TYPE* map) const;// position entite valide sur carte (pas bloqué?)
	int getV(const std::map<sf::Vector2i*, int>& m, sf::Vector2i* a) const;// recup premier monstre trouvé
	bool blink();// combat anim

	void tryToLaunchABattle(sf::Vector2i player_pos);// check les coord du perso et monstgre

	bool noMonsterHere(sf::Vector2i position) const; // regarde si la case adj est occupé par monstre


	static int manhattanDistance(const sf::Vector2i& a, const sf::Vector2i& b);// distance mnhnattan
private:
	sf::View m_view;

	std::vector<Entite*> m_entities;// list des entites sur la carte
	Map* m_map;// carte

	sf::SoundBuffer m_base_battle_sound_buffer;// buffer son du combat
	sf::Sound m_base_battle_sound;// son du comabt

	Sample m_collision; // son collision
	sf::Music m_main_song;// son theme pcp
	Sample m_menu_song;// pareil mais pour menu

	int m_battle_issue;// qui qui gagne


	bool t_fight;// en combat?
	sf::Clock t_intro;// pour le combat anim
	sf::Clock t_blink;// pour le combat anim
	bool blink_boom;// pour le combat anim
	bool t_already_started;// pour le combat anim
	int fade;// pour le combat anim

	Joueur *m_player;// player
	sf::Clock m_movement_clock;// deplacement fluide (ou presque)

	Menu* m_menu;// menu

	std::vector<Monstre*> m_monsters;// les monstres
	sf::Vector2i  * m_monster_pos; // pos des monstres

	Monstre* m_monster_buffer; // monstre a coté
	bool m_just_left_a_battle; // viens de quitter un cbt?


	int m_map_size;// taille carte

	int m_monster_number;// nb monstre carte

	sf::Text m_end_text;// anim fin
	bool m_end;// anim fin
	sf::Clock m_end_clk;// anim fin
	sf::Clock m_end_scale;// anim fin
	bool m_end_scale_on;// anim fin
	bool m_NOW_THE_END;// anim fin

	sf::Music m_end_music;// music fin

};

