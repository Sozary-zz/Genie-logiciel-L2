#pragma once
<<<<<<< HEAD
#DEFINE DATASAVEPERS "./data/loading/Player.txt"
#ifndef JOUEUR
#define JOUEUR


class Joueur : public Entite {

=======
#include <SFML\Graphics.hpp>
#include "AnimatedSprite.hpp"
#include "GameState.hpp"
#include "Entity.h"
>>>>>>> 45ebc2628ea955ae03c5e101dd04afa2b2fa2ddb

class Joueur : public Entite, public sf::Drawable, public sf::Transformable {
	
public:

	Joueur();
	Joueur(std::string classe,std::string pseudo, int pvmax, int mana, int armure, int force,int comp1,int comp2,int comp3,int comp4);

	~Joueur();
	Competence * choisir_competence(int i_comp);

	std::vector<std::string> recupNomCompetences() const;

	void up();
	void down();
	void left();
	void right();
	bool isWalking();
	void RempirCompetence();


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

};
