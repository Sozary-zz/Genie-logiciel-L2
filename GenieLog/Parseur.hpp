#pragma once
#include "Competence.h"
#include "GameState.hpp"

#define DATASAVECOMP "data\\loading\\Comp.txt"
#define DATASAVEPLAYER "data\\loading\\Character.txt"
#define DATASAVEMONSTEr "data\\loading\\Monster.txt"

class Joueur;
class Monstre;

Competence * ChargerCompetence(int numero);
Joueur * ChargerJoueur(std::string pseudo, std::string nomclasse);
void nombrePossible(string contenu, char& classecomplete,char type);
Monstre * ChargerMonstre(string pseudo);
