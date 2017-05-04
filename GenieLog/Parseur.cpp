#include "Parseur.hpp"


Competence * ChargerCompetence(int numero){

	ifstream fichier(DATASAVECOMP, ios::in);	
	string contenu;
	string toto;
	string compnumber = to_string(numero);

	if(fichier){
		getline(fichier,contenu);
		getline(fichier,contenu);
		contenu = " ";
		while(contenu != ""){
			getline(fichier, contenu);
			cout << contenu << endl;
			toto = contenu.substr(0,contenu.find("/"));
			if(compnumber == toto){ // on a trouve la competence qu'on cherchait
				string nom;
				int damages,ratio,tempsincantation,coutmana;
				
				// recupere la ligne sans le numero de la competence
				contenu = contenu.substr(contenu.find("/") + 1,contenu.length());
				toto = contenu.substr(0,contenu.find("/"));
				nom = toto;
				// nom chargé
				
				contenu = contenu.substr(contenu.find("/") + 1,contenu.length());
				toto = contenu.substr(0,contenu.find("/"));
				damages = stoi(toto);
				// damages chargés

				contenu = contenu.substr(contenu.find("/") + 1,contenu.length());
				toto = contenu.substr(0,contenu.find("/"));
				ratio = stoi(toto);
				// ratio chargé
				
				contenu = contenu.substr(contenu.find("/") + 1,contenu.length());
				toto = contenu.substr(0,contenu.find("/"));
				tempsincantation = stoi(toto);
				//temps incantation chargé
				
				contenu = contenu.substr(contenu.find("/") + 1,contenu.length());
				toto = contenu.substr(0,contenu.find("/"));
				coutmana = stoi(toto);
				//cout mana chargé				
				
				fichier.close();
				return new Competence(nom,damages,ratio,tempsincantation,coutmana);
			}
		}
	}
}


