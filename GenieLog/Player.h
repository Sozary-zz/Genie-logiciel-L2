#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "GameState.hpp"
#include "Entity.h"

#define TILE_SIZE 64.f
#define TIME_ACTION .2f


class Joueur : public Entite, public sf::Drawable {

public:

	Joueur();
	Joueur(std::string pseudo, std::string classe, int pvmax, int mana, int armure, int force, int comp1, int comp2, int comp3, int comp4);
	Joueur(std::string pseudo, std::string classe, int pvmax, int mana, int armure, int force);
	~Joueur();
	Competence * choisir_competence(int i_comp);

	std::vector<std::string> recupNomCompetences() const;


	void RempirCompetence();
	void adjustPos(sf::Vector2i grid, sf::Vector2i position, sf::Vector2f scale, sf::Vector2f speed);// positionne le jouer dans fenetre

	void left();//demarre directions
	void up();
	void down();
	void right();

	void continueAnim(sf::Time frame);// anim avance

	sf::Vector2i positionInGrid();// savoir la pos du joueur

	bool isRunning();// anim en cours?

	void _left_();// continue l anim de marcher
	void _up_();
	void _down_();
	void _right_();

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
	int *m_walking_positions;// positons d avancement (spritesheet)
	int m_walking_compt;// etape 

	sf::Vector2f m_speed;//vitesse



	bool m_anim_running;// on marche?
	sf::Clock m_next_anim;// anim suivante 
	sf::Vector2i m_position_in_the_grid;// pos

};
