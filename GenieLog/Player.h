#pragma once
#include <SFML\Graphics.hpp>
#include "GameState.hpp"
#include "Entity.h"

class Joueur : public Entite, public sf::Drawable/*, public sf::Transformable*/ {
	
public:

	Joueur();
	Joueur(std::string pseudo, int pvmax, int mana, int armure, int force);

	~Joueur();
	Competence * choisir_competence(int i_comp);

	std::vector<std::string> recupNomCompetences() const;

	
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
