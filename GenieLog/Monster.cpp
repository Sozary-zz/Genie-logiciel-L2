#include <iostream>
#include "Monster.h"

using namespace std;

Monstre::Monstre(string classe, int pvMax, int mana, int armure, int force) : Entite(classe, pvMax, mana, armure, force)
{
}

Monstre::~Monstre()
{
}

Competence * Monstre::choisir_competence()
{
	return new Competence("Griffure", 15, 1, 5, 0);
}

void Monstre::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
}
