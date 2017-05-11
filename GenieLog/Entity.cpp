#include <iostream>
#include "Entity.h"

using namespace std;

Entite::Entite() :
	m_nom(""), m_pvMax(0), m_pv(0), m_mana(0), m_manaMax(0), m_Armure(0), m_force(0),m_orientation(DOWN)
{

}

Entite::Entite(string nom, int pvmax, int manamax, int armure, int force) {
	m_nom = nom;
	m_pvMax = pvmax;
	m_pv = pvmax;
	m_manaMax = manamax;
	m_mana = manamax;
	m_Armure = armure;
	m_force = force;
	m_orientation = DOWN;
}

Entite::~Entite()
{
	for (auto&x : tableau_competence)
		delete x;
}

bool Entite::estVivant()
{
	return (m_pv > 0);
}



void Entite::prendreDegats(int nombrededmgdelacomp)
{
	//nombrededmgdelacomp -= m_Armure;

	//if (nombrededmgdelacomp <= 0)
	//	nombrededmgdelacomp = 0;

	m_pv = m_pv - nombrededmgdelacomp;

	//cout << "Le " << m_nom << " a perdu " << nombrededmgdelacomp << " points de vie" << endl;

//	if (!estVivant())	cout << ", le tuant" << endl;
//	else				cout << endl;

}

string Entite::recupNom() {
	return m_nom;
}

DIRECTION Entite::recupOrientation()
{
	return m_orientation;
}

void Entite::setOrientation(DIRECTION d)
{
	m_orientation = d;
	
}
