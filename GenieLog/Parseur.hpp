#pragma once
#include "Competence.h"
#include "GameState.hpp"

#define DATASAVECOMP "data\\loading\\Comp.txt"
#define DATASAVEPLAYER "data\\loading\\Character.txt"
#define DATASAVEMONSTER "data\\loading\\Monster.txt"
#define NOMBREMAX 1000

class Joueur;
class Monstre;

Competence * ChargerCompetence(int numero);// charge comp
Joueur * ChargerJoueur(std::string pseudo, std::string nomclasse);//charge joeueur
void nombrePossible(string contenu, char& classecomplete,char type);// nb possible de classe
Monstre * ChargerMonstre(string pseudo);//charge ennemie
