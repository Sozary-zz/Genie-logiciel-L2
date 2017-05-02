

#ifndef COMPETENCE
#define COMPETENCE

#include <string>
#include <iostream>
#include <fstream>

using namespace std;


class Competence {

private:
	std::string m_nom;
	int m_damages;
	int m_ratio;
	int m_temps_incantation;
	int m_coutmana;
	//effet?

public:
	Competence(std::string nom, int damages, int ratio, int tempsincantation, int coutmana);
	Competence();
	~Competence();
	void setRatio(int ration) { m_ratio = ration; };
	std::string getNom();
	int getDamages();
	int getRatio();
	int getTempsIncantation();
	int getCoutMana();
};

#endif
