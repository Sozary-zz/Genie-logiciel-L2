#include <iostream>
#include "Player.h"

using namespace sf;
using namespace std;

Joueur::Joueur(string pseudo, int pvmax, int mana, int armure, int force) : Entite(pseudo, pvmax, mana, armure, force), nb_objet_max(30), nb_equipement_max(6), nb_competence_max(5), m_pseudo(pseudo)
, m_walking_compt(0), m_orientation(DOWN),m_animated_sprite(seconds(.2f),true,false), m_anim_running(false), m_running_cmpt(0){
	m_inventaire = new Objet[nb_objet_max];
	m_equipement = new Objet[nb_equipement_max];
	RempirCompetence();

	m_inventaire = new Objet[nb_objet_max];
	m_equipement = new Objet[nb_equipement_max];

	GameState::texture_manager->addElement("character_sprite", "data\\character.png"); // pwet

	m_walking_positions = new int[4]
	{ 8,10,9,11 };


	//m_sprite.setTextureRect(IntRect(m_walking_compt* TILE_SIZE, m_walking_positions[m_orientation] * TILE_SIZE, TILE_SIZE, TILE_SIZE));

	Animation walking_down, walking_up, walking_right, walking_left;
	walking_down.setSpriteSheet(GameState::texture_manager->getElement("character_sprite"));
	walking_right.setSpriteSheet(GameState::texture_manager->getElement("character_sprite"));
	walking_up.setSpriteSheet(GameState::texture_manager->getElement("character_sprite"));
	walking_left.setSpriteSheet(GameState::texture_manager->getElement("character_sprite"));

	for (int i = 0; i < 9; ++i)
	{
		walking_down.addFrame(IntRect(i * 64, m_walking_positions[DOWN] * 64, 64, 64));
		walking_right.addFrame(IntRect(i * 64, m_walking_positions[RIGHT] * 64, 64, 64));
		walking_up.addFrame(IntRect(i * 64, m_walking_positions[UP] * 64, 64, 64));
		walking_left.addFrame(IntRect(i * 64, m_walking_positions[LEFT] * 64, 64, 64));
	}
	m_animations.push_back(walking_up);
	m_animations.push_back(walking_down);
	m_animations.push_back(walking_left);
	m_animations.push_back(walking_right);

	m_current_anim = &m_animations[m_orientation];


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
	m_animated_sprite.setPosition((Vector2f)position);
	m_animated_sprite.setScale(scale);
	m_speed = speed;
}

void Joueur::left()
{
	m_orientation = LEFT;

	m_current_anim = &m_animations[m_orientation];
	m_animated_sprite.play(*m_current_anim);
	m_anim_running = true;
	m_running_cmpt = 0;
}

void Joueur::up()
{
	m_orientation = UP;

	m_current_anim = &m_animations[m_orientation];
	m_animated_sprite.play(*m_current_anim);
	m_anim_running = true;
	m_running_cmpt = 0;

}

void Joueur::down()
{
	m_orientation = DOWN;

	m_current_anim = &m_animations[m_orientation];
	m_animated_sprite.play(*m_current_anim);
	m_anim_running = true;
	m_running_cmpt = 0;

}

void Joueur::right()
{
	m_orientation = RIGHT;
	m_current_anim = &m_animations[m_orientation];
	m_animated_sprite.play(*m_current_anim);
	m_anim_running = true;
	m_running_cmpt = 0;

}

void Joueur::continueAnim(Time frame)
{
	switch (m_orientation)
	{
	case UP:
		m_animated_sprite.move(0,-m_speed / 9.f);
		break;
	case DOWN:
		m_animated_sprite.move(0,m_speed / 9.f);
		break;
	case LEFT:
		m_animated_sprite.move(-m_speed / 9.f, 0);
		break;
	case RIGHT:
		m_animated_sprite.move(m_speed / 9.f, 0);
		break;
	}
	

	m_animated_sprite.update(frame);

	if (m_running_cmpt >= 9)
	{
		m_animated_sprite.stop();
		m_anim_running = false;
		m_running_cmpt = 0;
		return;
	}

	m_running_cmpt++;
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
	target.draw(m_animated_sprite);
}
