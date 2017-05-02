#include <iostream>
#include "Player.h"

using namespace std;

Joueur::Joueur() :nb_objet_max(30), nb_equipement_max(6), nb_competence_max(5)
{
	m_inventaire = new Objet[nb_objet_max];
	m_equipement = new Objet[nb_equipement_max];

}

Joueur::~Joueur()
{
	delete[] m_inventaire;
	delete[] m_equipement;
}

Competence * Joueur::choisir_competence(int i_comp)
{
	auto x = tableau_competence[i_comp];
	x->setRatio(x->getRatio()*m_force);
	return new Competence(x->getNom(), x->getDamages() + x->getRatio()*m_force, 0, x->getTempsIncantation(), x->getCoutMana());

}



std::vector<std::string> Joueur::recupNomCompetences() const
{
	vector<string> res;
	for (auto&x : tableau_competence)
		res.push_back(x->getNom());

	return res;
}

Joueur::Joueur(string pseudo, int pvmax, int mana, int armure, int force) : Entite(pseudo, pvmax, mana, armure, force), nb_objet_max(30), nb_equipement_max(6), nb_competence_max(5), m_pseudo(pseudo)
{
	m_inventaire = new Objet[nb_objet_max];
	m_equipement = new Objet[nb_equipement_max];
	RempirCompetence();
}
// iuehdiuehd //
//Fonction TEST
void Joueur::RempirCompetence()
{
	tableau_competence.push_back(new Competence("griffe", 10, 1, 5, 0));
	tableau_competence.push_back(new Competence("Morsure", 25, 2, 10, 1));
	tableau_competence.push_back(new Competence("Pet", 1, 0, 25, 0));
	tableau_competence.push_back(new Competence("Mignon Sourire", 0, 0, 2, 0));
}
