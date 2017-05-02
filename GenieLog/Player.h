#include "Entity.h"
#pragma once
#ifndef JOUEUR
#define JOUEUR


class Joueur : public Entite {


public:

	Joueur();
	Joueur(std::string pseudo, int pvmax, int mana, int armure, int force);
	
	~Joueur();
	Competence * choisir_competence(int i_comp);

	 std::vector<std::string> recupNomCompetences() const;

	void RempirCompetence();

private:
	std::string m_pseudo;
	Objet* m_inventaire;
	Objet* m_equipement;
	const int nb_objet_max;
	const int nb_competence_max;
	const int nb_equipement_max;//t
};

#endif
