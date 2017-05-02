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

				return new Competence(nom,damages,ratio,tempsincantation,coutmana);
			}
		}
			fichier.close();
		cout << "Competence numero " << numero << " est introuvable dans " << DATASAVECOMP << endl;
	}	
	else{
		cout << "Le fichier de chargement " << DATASAVECOMP << " est introuvable !" << endl;
	}	
}	
