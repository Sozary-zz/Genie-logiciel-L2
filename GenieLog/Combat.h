#ifndef COMBAT
#define COMBAT

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <iostream>
#include "Player.h"
#include "Monster.h"

using namespace std;


bool combattre(Joueur * player, Monstre * monstre);
void remplirBuffer(string ** buffer,int tick,int specification,Monstre *,Joueur * );
void remplirCompetence(int ligneBuffer, string ** buffer, Competence *comp,int tick);

#endif
