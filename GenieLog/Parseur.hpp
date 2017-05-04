#ifndef PARSEUR
#define PARSEUR

#include "Competence.h"
#include "Player.h"

#define DATASAVECOMP "data\\loading\\Comp.txt"
#define DATASAVEPLAYER "data\\loading\\Player.txt"

Competence * ChargerCompetence(int numero);
Joueur * ChargerJoueur(std::string psuedo, std::string nomclasse);


#endif
