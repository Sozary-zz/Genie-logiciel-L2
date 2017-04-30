#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include <random>
#include <algorithm>
#include "GameState.hpp"
#include "Combat.h"
#include "SkillsBoard.h"
#include "EditList.h"

struct Turn {
	int tick_rest; // ticks restant to do the turn
	Entite* entity;
	int type;
	Competence* skill;
};
class GameBattle: public GameState
{
public:
	GameBattle(Game* game,Joueur* player, Monstre* monster, int* battle_issue);
	virtual void draw(const float delta_time) ;
	virtual void update(const float delta_time);
	virtual void eventLoop();

private:
	void updateBars(int type);
	void player_attack();
	void monster_attack();
	bool endBattle();

private:
	sf::View m_view;
	sf::Sprite m_background;

	sf::RectangleShape m_hp_enemy[3];
	sf::RectangleShape m_hp_player[3];


	sf::SoundBuffer m_base_battle_sound_buffer;
	sf::Sound m_base_battle_sound;

	std::vector<sf::Text>  m_texts;
	sf::Sprite entities[2];

	int m_tick;
	std::string ** m_buffer;
	std::mt19937 m_gen;
	std::uniform_int_distribution<> m_dis;

	Monstre * m_monster;
	Joueur* m_player;

	SkillsBoard* m_skills_board;

	sf::Vector2f m_enemy_bar;
	sf::Vector2f m_player_bar;

	std::vector<Turn> m_turns;

	EditList* m_actions;

	int* m_battle_issue;

};

