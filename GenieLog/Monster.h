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
	Monstre(std::string classe, int pvMax, int mana, int armure, int force,  int comp1, int comp2, int comp3, int comp4);
	~Monstre();

	void adjustPos(sf::Vector2i grid, sf::Vector2i position, sf::Vector2f scale, DIRECTION orientation);

	Competence * choisir_competence();

	sf::Vector2i recupPos() const;

	void textureUpdate();
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Sprite m_sprite;

	sf::Vector2i m_position;
	sf::Vector2i m_grid_pos;
};

#endif
