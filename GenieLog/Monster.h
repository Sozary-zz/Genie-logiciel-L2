#include "Entity.h"
#include <SFML\Graphics.hpp>
#include <vector>
// 32 x 32
#define BASIC_M_P Vector2i(260,258)
#define FINAL_M_P Vector2i(325,1290)

#ifndef MONSTRE
#define MONSTRE

class Monstre : public Entite , public sf::Drawable {


public:
	Monstre() {}
	Monstre(std::string classe, int pvMax, int mana, int armure, int force, sf::Vector2i position,sf::Vector2f scale,DIRECTION orientation);
	~Monstre();

	Competence * choisir_competence();
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void textureUpdate();
private:
	sf::Sprite m_sprite;
	DIRECTION m_orientation;
};

#endif
