#include "Entity.h"
#include <SFML\Graphics.hpp>

#ifndef MONSTRE
#define MONSTRE

class Monstre : public Entite , public sf::Drawable {


public:
	Monstre() {}
	Monstre(std::string classe, int pvMax, int mana, int armure, int force);
	~Monstre();

	Competence * choisir_competence();
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif
