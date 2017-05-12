#include <string>
#include <vector>
#include "Competence.h"
#include "objet.h"
#include "Parseur.hpp"

#ifndef ENTITE
#define ENTITE
enum DIRECTION {
	UP, DOWN, LEFT, RIGHT
};
class Entite {


public:
	Entite();
	Entite(std::string nom, int pvmax, int manamax, int armure, int force);
	~Entite();

	bool estVivant();
	void prendreDegats(int nombrededmgdelacomp);
	std::string recupNom();

	int recupMaxVie() { return m_pvMax; };
	int recupVie() { return m_pv; };
	
	DIRECTION recupOrientation();
	void setOrientation(DIRECTION d);


protected:
	//    Tile* position;
	std::string m_nom;
	int m_pvMax;
	int m_pv;
	int m_manaMax;
	int m_mana;
	int m_Armure;
	int m_force;
	std::vector<Competence*> tableau_competence;
	DIRECTION m_orientation;
};

#endif 
