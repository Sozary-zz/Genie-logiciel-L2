#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "GameState.hpp"
#include "AnimatedSprite.hpp"
#include "Entity.h"
#define TILE_SIZE 64.f

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
	void adjustPos(sf::Vector2i position, sf::Vector2f scale, float speed);

	void left();
	void up();
	void down();
	void right();

	void continueAnim(sf::Time frame);

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

	float m_speed;

	DIRECTION m_orientation;

	std::vector<Animation> m_animations;
	Animation* m_current_anim;
	AnimatedSprite m_animated_sprite;

	bool m_anim_running;
	int m_running_cmpt;

};
