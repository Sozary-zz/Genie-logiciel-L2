#pragma once
#include <SFML\Graphics.hpp>
#include "AnimatedSprite.hpp"
#include "GameState.hpp"
#include "Entity.h"

class Joueur : public Entite, public sf::Drawable, public sf::Transformable {
	
public:

	Joueur();
	Joueur(std::string pseudo, int pvmax, int mana, int armure, int force);

	~Joueur();
	Competence * choisir_competence(int i_comp);

	std::vector<std::string> recupNomCompetences() const;
	void run();
	void up();
	void down();
	void left();
	void right();
	bool isWalking();
	void stop_running();
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

	Animation *m_walking_anim;
	Animation* m_current_anim;
	AnimatedSprite m_animated;

	// SFML PART
	sf::Sprite m_sprite;
	
	bool m_is_walking;
};
