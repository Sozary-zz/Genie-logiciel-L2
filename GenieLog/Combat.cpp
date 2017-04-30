#include "Combat.h"


#define nbpersonnescombat 2

bool combattre(Joueur * player,Monstre * monstre){
	srand (time(NULL));
	string ** buffer = new string * [nbpersonnescombat];
	int random;
	int tick = 0;
	for(int i = 0 ; i < nbpersonnescombat ; i++){
		buffer[i] = new string[3];
	}
	remplirBuffer(buffer,tick,1000,monstre,player);
	while(42){
		tick = tick + 1;
		if(buffer[0][0] == to_string(tick)){
			if(buffer[1][0] == to_string(tick)){
				random = rand() % nbpersonnescombat;
				if(random == 0){
					cout << monstre->recupNom() << " utilise " << buffer[1][1] << endl;
					player->prendreDegats(atoi(buffer[1][2].c_str()));
					if(player->estVivant()){
						cout << player->recupNom() << " utilise " << buffer[1][1] << endl;
						monstre->prendreDegats(atoi(buffer[0][2].c_str()));
						if(monstre->estVivant()){					
							remplirBuffer(buffer,tick,1000,monstre,player);
						}
						else{
							return true;
						}	
					}
					else{
						return false;
					}
				}
				else{
					cout << player->recupNom() << " utilise " << buffer[1][1] << endl;
					monstre->prendreDegats(atoi(buffer[0][2].c_str()));
					if(monstre->estVivant()){						
						cout << monstre->recupNom() << " utilise " << buffer[1][1] << endl;
						player->prendreDegats(atoi(buffer[1][2].c_str()));
						if(player->estVivant()){					
							remplirBuffer(buffer,tick,1000,monstre,player);
						}
						else{
							return false;
						}	
					}
					else{
						return true;
					}
				}
			}
			else{
				cout << player->recupNom() << " utilise " << buffer[1][1] << endl;
				monstre->prendreDegats(atoi(buffer[0][2].c_str()));
				if(monstre->estVivant()){
					remplirBuffer(buffer,tick,0,monstre,player);
				}
				else{
					return true;
				}
			}
		}
		else if(buffer[1][0] == to_string(tick)){
			cout << monstre->recupNom() << " utilise " << buffer[1][1] << endl;
			player->prendreDegats(atoi(buffer[1][2].c_str()));
			if(player->estVivant()){
				remplirBuffer(buffer,tick,1,monstre,player);
			}
			else{
				return false;
			}
		}
		
	}
}


void remplirCompetence(int ligneBuffer, string ** buffer, Competence * comp,int tick){
	buffer[ligneBuffer][0] = to_string(tick + comp->getTempsIncantation());
	buffer[ligneBuffer][1] = comp->getNom();
	buffer[ligneBuffer][2] = to_string(comp->getDamages());
}

void remplirBuffer(string ** buffer,int tick,int specification, Monstre * monstre, Joueur * player){
	Competence * comp;
	if(specification == 1000){	
		comp = monstre->choisir_competence();
		remplirCompetence(1,buffer,comp,tick);
		/*comp = player->choisir_competence();
		remplirCompetence(0,buffer,comp,tick);*/
	}
	else if(specification == 0){
		/*comp = player->choisir_competence();
		remplirCompetence(specification,buffer,comp,tick);*/
	}
	else if(specification == 1){
		comp = monstre->choisir_competence();
		remplirCompetence(specification,buffer,comp,tick);
	}
	return;
}
