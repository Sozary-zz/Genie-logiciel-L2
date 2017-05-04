#include <iostream>
#include "Player.h"

using namespace sf;
using namespace std;

Joueur::Joueur(string pseudo, int pvmax, int mana, int armure, int force) : Entite(pseudo, pvmax, mana, armure, force), nb_objet_max(30), nb_equipement_max(6), nb_competence_max(5), m_pseudo(pseudo)
, m_walking_compt(0), m_orientation(DOWN){
	m_inventaire = new Objet[nb_objet_max];
	m_equipement = new Objet[nb_equipement_max];
	RempirCompetence();

	m_inventaire = new Objet[nb_objet_max];
	m_equipement = new Objet[nb_equipement_max];

	GameState::texture_manager->addElement("character_sprite", "data\\character.png"); // pwet

	m_walking_positions = new int[4]
	{ 8,10,9,11 };

	m_sprite.setTexture(GameState::texture_manager->getElement("character_sprite"));
	m_sprite.setTextureRect(IntRect(m_walking_compt* TILE_SIZE, m_walking_positions[m_orientation] * TILE_SIZE, TILE_SIZE, TILE_SIZE));


}

Joueur::Joueur() :nb_objet_max(30), nb_equipement_max(6), nb_competence_max(5),
m_walking_compt(0)
{
	
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




//Fonction TEST
void Joueur::RempirCompetence()
{
	tableau_competence.push_back(new Competence("griffe", 10, 1, 5, 0));
	tableau_competence.push_back(new Competence("Morsure", 25, 2, 10, 1));
	tableau_competence.push_back(new Competence("Pet", 1, 0, 25, 0));
	tableau_competence.push_back(new Competence("Mignon Sourire", 0, 0, 2, 0));
}

void Joueur::adjustPos(Vector2i position, Vector2f scale, float speed)
{
	m_sprite.setPosition((Vector2f)position);
	m_sprite.setScale(scale);
	m_speed = speed;
}

void Joueur::left()
{
	if (m_orientation != LEFT)
	{
		m_walking_compt = 0;
		m_orientation = LEFT;
	}
	else
		m_walking_compt = (m_walking_compt + 1 >= 9) ? 0 : m_walking_compt + 1;
	m_sprite.setTextureRect(IntRect(m_walking_compt* TILE_SIZE, m_walking_positions[m_orientation] * TILE_SIZE, TILE_SIZE, TILE_SIZE));
	m_sprite.move(-m_speed, 0);
}

void Joueur::up()
{
	if (m_orientation != UP)
	{
		m_walking_compt = 0;
		m_orientation = UP;
	}
	else
		m_walking_compt = (m_walking_compt + 1 >= 9) ? 0 : m_walking_compt + 1;
	m_sprite.setTextureRect(IntRect(m_walking_compt* TILE_SIZE, m_walking_positions[m_orientation] * TILE_SIZE, TILE_SIZE, TILE_SIZE));
	m_sprite.move(0, -m_speed);
}

void Joueur::down()
{
	if (m_orientation != DOWN)
	{
		m_walking_compt = 0;
		m_orientation = DOWN;
	}
	else
		m_walking_compt = (m_walking_compt + 1 >= 9) ? 0 : m_walking_compt + 1;
	m_sprite.setTextureRect(IntRect(m_walking_compt* TILE_SIZE, m_walking_positions[m_orientation] * TILE_SIZE, TILE_SIZE, TILE_SIZE));
	m_sprite.move(0, m_speed);
}

void Joueur::right()
{
	if (m_orientation != RIGHT)
	{
		m_walking_compt = 0;
		m_orientation = RIGHT;
	}
	else
		m_walking_compt = (m_walking_compt + 1 >= 9) ? 0 : m_walking_compt + 1;
	m_sprite.setTextureRect(IntRect(m_walking_compt* TILE_SIZE, m_walking_positions[m_orientation] * TILE_SIZE, TILE_SIZE, TILE_SIZE));
	m_sprite.move(m_speed, 0);
}

void Joueur::init()
{
	m_walking_compt = 0;
	m_sprite.setTextureRect(IntRect(m_walking_compt* TILE_SIZE, m_walking_positions[m_orientation] * TILE_SIZE, TILE_SIZE, TILE_SIZE));

}

void Joueur::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_sprite);
}
