#include <iostream>
#include "Player.h"

using namespace sf;
using namespace std;

Joueur::Joueur(string pseudo,string classe, int pvmax, int mana, int armure, int force,int comp1,int comp2,int comp3,int comp4) : Entite(classe, pvmax, mana, armure, force), nb_objet_max(30), nb_equipement_max(6), nb_competence_max(5), m_pseudo(pseudo)
, m_walking_compt(0), m_orientation(DOWN), m_anim_running(false), m_position_in_the_grid(0,0){
	m_inventaire = new Objet[nb_objet_max];
	m_equipement = new Objet[nb_equipement_max];
	
	/*tableau_competence.push_back(ChargerCompetence(comp1));
	tableau_competence.push_back(ChargerCompetence(comp2));
	tableau_competence.push_back(ChargerCompetence(comp3));
	tableau_competence.push_back(ChargerCompetence(comp4));*/

	GameState::texture_manager->addElement("character_sprite", "data\\character.png"); // pwet

	m_walking_positions = new int[4]
	{ 8,10,9,11 };

	m_sprite.setTexture(GameState::texture_manager->getElement("character_sprite"));
	m_sprite.setTextureRect(IntRect(m_walking_compt* TILE_SIZE, m_walking_positions[m_orientation] * TILE_SIZE, TILE_SIZE, TILE_SIZE));
}

Joueur::Joueur(string pseudo, string classe, int pvmax, int mana, int armure, int force): Entite(classe, pvmax, mana, armure, force), nb_objet_max(30), nb_equipement_max(6), nb_competence_max(5), m_pseudo(pseudo)
, m_walking_compt(0), m_orientation(DOWN), m_anim_running(false), m_position_in_the_grid(0, 0) {
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
	delete[] m_walking_positions;
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

void Joueur::adjustPos(Vector2i grid,Vector2i position, Vector2f scale, Vector2f speed)
{
	m_position_in_the_grid = grid;
	m_sprite.setPosition((Vector2f)position);
	m_sprite.setScale(scale);
	m_speed = speed / 9.f;
}

void Joueur::left()
{
	cout << "gauche" << endl;
	m_position_in_the_grid.x--;
	m_orientation = LEFT;
	m_sprite.setTextureRect(IntRect(m_walking_compt* TILE_SIZE, m_walking_positions[m_orientation] * TILE_SIZE, TILE_SIZE, TILE_SIZE));
	m_anim_running = true;
	m_walking_compt = 0;
	m_next_anim.restart();

}

void Joueur::up()
{
	cout << "haut" << endl;

	m_position_in_the_grid.y--;
	m_orientation = UP;
	m_sprite.setTextureRect(IntRect(m_walking_compt* TILE_SIZE, m_walking_positions[m_orientation] * TILE_SIZE, TILE_SIZE, TILE_SIZE));
	m_anim_running = true;
	m_walking_compt = 0;
	m_next_anim.restart();

}

void Joueur::down()
{
	cout << "bas" << endl;

	m_position_in_the_grid.y++;
	m_orientation = DOWN;
	m_sprite.setTextureRect(IntRect(m_walking_compt* TILE_SIZE, m_walking_positions[m_orientation] * TILE_SIZE, TILE_SIZE, TILE_SIZE));
	m_anim_running = true;
	m_walking_compt = 0;
	m_next_anim.restart();

}

void Joueur::right()
{
	cout << "droite" << endl;

	m_position_in_the_grid.x++;
	m_orientation = RIGHT;
	m_sprite.setTextureRect(IntRect(m_walking_compt* TILE_SIZE, m_walking_positions[m_orientation] * TILE_SIZE, TILE_SIZE, TILE_SIZE));
	m_anim_running = true;
	m_walking_compt = 0;
	m_next_anim.restart();

}

void Joueur::continueAnim(Time frame)
{
	if (m_next_anim.getElapsedTime().asSeconds() >= TIME_ACTION / 9.f) {
		Vector2f res;
		switch (m_orientation)
		{
		case UP:
			res = { 0,-m_speed.y };
			break;
		case DOWN:
			res = { 0,m_speed.y };
			break;
		case LEFT:
			res = { -m_speed.x ,0 };
			break;
		case RIGHT:
			res = { m_speed.x ,0 };
			break;
		}

		m_sprite.move(res);
		m_sprite.setTextureRect(IntRect(m_walking_compt* TILE_SIZE, m_walking_positions[m_orientation] * TILE_SIZE, TILE_SIZE, TILE_SIZE));

		if (m_walking_compt >= 8)
		{

			m_anim_running = false;
			m_walking_compt = 0;
			m_sprite.setTextureRect(IntRect(m_walking_compt* TILE_SIZE, m_walking_positions[m_orientation] * TILE_SIZE, TILE_SIZE, TILE_SIZE));
			return;
		}

		m_walking_compt++;
		m_next_anim.restart();
	}

}

sf::Vector2i Joueur::positionInGrid()
{
	return m_position_in_the_grid;
}

bool Joueur::isRunning()
{
	return m_anim_running;
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
