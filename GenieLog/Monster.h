#include "Entity.h"


#ifndef MONSTRE
#define MONSTRE

class Monstre : public Entite {


public:
	Monstre() {}
	Monstre(std::string classe, int pvMax, int mana, int armure, int force);
	~Monstre();

	Competence * choisir_competence();

};

#endif
