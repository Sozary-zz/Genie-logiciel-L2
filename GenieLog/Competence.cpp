#include "Competence.h"

Competence::Competence(){
	m_nom = "default";
	m_damages = 0;
	m_ratio = 0;
	m_temps_incantation = 0;
	m_coutmana = 0;
}

Competence::Competence(string nom,int damages,int ratio,int tempsincantation,int coutmana){
	m_nom = nom;
	m_damages = damages;
	m_ratio = ratio;
	m_temps_incantation = tempsincantation;
	m_coutmana = coutmana;
}

Competence::~Competence(){


}

string Competence::getNom(){
	return m_nom;
}

int Competence::getDamages(){
	return m_damages;
}

int Competence::getRatio(){
	return m_ratio;
}

int Competence::getTempsIncantation(){
	return m_temps_incantation;
}

int Competence::getCoutMana(){
	return m_coutmana;
}	
