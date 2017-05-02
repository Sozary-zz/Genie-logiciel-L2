#include <iostream>
#include "Player.h"

using namespace sf;
using namespace std;

Joueur::Joueur() :nb_objet_max(30), nb_equipement_max(6), nb_competence_max(5),
m_animated(seconds(.2f),true,false), m_is_walking(false)
{
	m_inventaire = new Objet[nb_objet_max];
	m_equipement = new Objet[nb_equipement_max];

	GameState::texture_manager->addElement("character_sprite", "data\\character.png"); // pwet

	m_walking_anim = new Animation[4]; // down/left/right/up

	int y_pos = 0;
	for (int i = 0; i < 4; ++i)
	{
		m_walking_anim[i].setSpriteSheet(GameState::texture_manager->getElement("character_sprite"));
		switch (i)
		{
		case 0:y_pos = 640; break;
		case 1:y_pos = 576; break;
		case 2:y_pos = 704; break;
		case 3:y_pos = 512; break;

		}
		for (int k = 0; k < 9; ++k)
			m_walking_anim[i].addFrame(IntRect(64 * k, y_pos, 64, 64));
	}
	m_current_anim = &m_walking_anim[0];

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

void Joueur::run() {
	m_is_walking = true;
}

void Joueur::up()
{
	m_current_anim = &m_walking_anim[3];
	move(0, -10);
}

void Joueur::down()
{
	m_current_anim = &m_walking_anim[0];	move(0, 10);
}

void Joueur::left()
{
	m_current_anim = &m_walking_anim[1];	move(-10,0);
}

void Joueur::right()
{
	m_current_anim = &m_walking_anim[2];	move(10,0);
}

bool Joueur::isWalking()
{
	return m_is_walking ;
}

void Joueur::stop_running()
{
	m_is_walking = false;
}

Joueur::Joueur(string pseudo, int pvmax, int mana, int armure, int force) : Entite(pseudo, pvmax, mana, armure, force), nb_objet_max(30), nb_equipement_max(6), nb_competence_max(5), m_pseudo(pseudo)
{
	m_inventaire = new Objet[nb_objet_max];
	m_equipement = new Objet[nb_equipement_max];
	RempirCompetence();
}


//Fonction TEST
void Joueur::RempirCompetence()
{
	tableau_competence.push_back(new Competence("griffe", 10, 1, 5, 0));
	tableau_competence.push_back(new Competence("Morsure", 25, 2, 10, 1));
	tableau_competence.push_back(new Competence("Pet", 1, 0, 25, 0));
	tableau_competence.push_back(new Competence("Mignon Sourire", 0, 0, 2, 0));
}

void Joueur::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_animated);
}
