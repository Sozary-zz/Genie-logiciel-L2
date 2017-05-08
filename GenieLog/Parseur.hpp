#pragma once
#include "Competence.h"
#include "GameState.hpp"

#define DATASAVECOMP "data\\loading\\Comp.txt"
#define DATASAVEPLAYER "data\\loading\\Player.txt"
class Joueur;
Competence * ChargerCompetence(int numero);
Joueur * ChargerJoueur(std::string pseudo, std::string nomclasse);

