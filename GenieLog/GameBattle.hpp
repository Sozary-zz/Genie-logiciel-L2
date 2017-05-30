#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include <random>
#include <algorithm>
#include "GameState.hpp"
#include "Combat.h"
#include "SkillsBoard.h"
#include "EditList.h"
struct Sample {// son de jeu manipulable
	sf::SoundBuffer sample_buffer;
	sf::Sound sample;
	bool running;
	sf::Clock sample_clock;
	void load(std::string path) {
		sample_buffer.loadFromFile(path);
		sample.setBuffer(sample_buffer);

	}
	void run() {
		running = true;
		sample.play();
		sample_clock.restart();
	}
	void update() {
		if (sample_clock.getElapsedTime().asSeconds() >= sample_buffer.getDuration().asSeconds())
		{
			sample.stop();
			running = false;
		}
	}

};

struct Turn {// tour de jey
	int tick_rest; // restant ticks  to do the turn
	Entite* entity;
	int type;
	Competence* skill;
};
class GameBattle: public GameState
{
public:
	GameBattle(Game* game,Joueur* player, Monstre* monster, int* battle_issue,std::vector<Monstre*>* monsters);
	~GameBattle();
	virtual void draw(const float delta_time) ;
	virtual void update(const float delta_time);
	virtual void eventLoop();

private:
	void updateBars(int type);// change la ligne de vie
	void player_attack();//joeuur joue
	void monster_attack();// monstre joue
	bool endBattle();// fin combat?

private:
	sf::View m_view;
	sf::Sprite m_background;

	sf::RectangleShape m_hp_enemy[3];// barre de vie monstre
	sf::RectangleShape m_hp_player[3];// barre de vie joueur


	sf::SoundBuffer m_base_battle_sound_buffer;// son de base buffer
	sf::Sound m_base_battle_sound;// son de base

	std::vector<sf::Text>  m_texts;// textes
	sf::Sprite entities[2];// entites

	int m_tick;// tours de jeu compteur
	std::string ** m_buffer;// infos combat
	std::mt19937 m_gen;// pour random
	std::uniform_int_distribution<> m_dis;// pour random

	Monstre * m_monster;// monstre
	Joueur* m_player;// jkoeur

	SkillsBoard* m_skills_board;// tableau skill

	sf::Vector2f m_enemy_bar;//barre enemie infos
	sf::Vector2f m_player_bar;// barre player infos

	std::vector<Turn> m_turns;// tours de jeu

	EditList* m_actions;// liste d aciton possibles

	int* m_battle_issue;//fin combat (qui gagne)

	Sample m_attack;// son attack
	Sample m_final_attack;// son final
	std::vector<Monstre*>* m_monsters;// le monstre tué disparait

	bool m_have_to_stop;// fin combat
	bool m_action_occured;// player a selec une attaque

	sf::Clock m_waiting_for_message;//attente dialogue combat
	bool m_have_to_wait_for_message;//attente dialogue combat

};

