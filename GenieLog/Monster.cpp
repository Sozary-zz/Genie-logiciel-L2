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
	return new Competence("CACA", 10, 1, 5, 0);
}
