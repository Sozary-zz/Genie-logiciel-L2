#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "GameState.hpp"
#include "AnimatedSprite.hpp"
#include "Entity.h"

#define TILE_SIZE 64.f
#define TIME_ACTION .2f

enum DIRECTION {
	UP, DOWN, LEFT, RIGHT
};
class Joueur : public Entite, public sf::Drawable {

public:

	Joueur();
	Joueur(std::string pseudo, int pvmax, int mana, int armure, int force);

	~Joueur();
	Competence * choisir_competence(int i_comp);

	std::vector<std::string> recupNomCompetences() const;


	void RempirCompetence();
	void adjustPos(sf::Vector2i grid, sf::Vector2i position, sf::Vector2f scale, sf::Vector2f speed);

	void left();
	void up();
	void down();
	void right();

	void continueAnim(sf::Time frame);

	sf::Vector2i positionInGrid();

	bool isRunning();

	void init();

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	std::string m_pseudo;
	Objet* m_inventaire;
	Objet* m_equipement;
	const int nb_objet_max;
	const int nb_competence_max;
	const int nb_equipement_max;

	// SFML PART
	sf::Sprite m_sprite;
	int *m_walking_positions;
	int m_walking_compt;

	sf::Vector2f m_speed;

	DIRECTION m_orientation;

	bool m_anim_running;
	sf::Clock m_next_anim;
	sf::Vector2i m_position_in_the_grid;

};
