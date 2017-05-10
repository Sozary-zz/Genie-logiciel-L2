#include "Parseur.hpp"


Competence * ChargerCompetence(int numero) {

	ifstream fichier(DATASAVECOMP, ios::in);
	string contenu;
	string lignefichier;
	string compnumber = to_string(numero);

	if (fichier) {
		getline(fichier, contenu);
		getline(fichier, contenu);
		contenu = " ";
		while (contenu != "") {
			getline(fichier, contenu);
			lignefichier = contenu.substr(0, contenu.find("/"));
			if (compnumber == lignefichier) { // on a trouve la competence qu'on cherchait
				string nom;
				string damages, ratio, tempsincantation, coutmana;

				// recupere la ligne sans le numero de la competence
				contenu = contenu.substr(contenu.find("/") + 1, contenu.length());
				lignefichier = contenu.substr(0, contenu.find("/"));
				nom = lignefichier;
				// nom chargé

				contenu = contenu.substr(contenu.find("/") + 1, contenu.length());
				lignefichier = contenu.substr(0, contenu.find("/"));
				damages = lignefichier;
				// damages chargés

				contenu = contenu.substr(contenu.find("/") + 1, contenu.length());
				lignefichier = contenu.substr(0, contenu.find("/"));
				ratio = lignefichier;
				// ratio chargé

				contenu = contenu.substr(contenu.find("/") + 1, contenu.length());
				lignefichier = contenu.substr(0, contenu.find("/"));
				tempsincantation = lignefichier;
				//temps incantation chargé

				contenu = contenu.substr(contenu.find("/") + 1, contenu.length());
				lignefichier = contenu.substr(0, contenu.find("/"));
				coutmana = lignefichier;
				//cout mana chargé				

				fichier.close();
				if (nom != "" && damages != "" && ratio != "" && tempsincantation != "" && coutmana != "") {
					return new Competence(nom, stoi(damages), stoi(ratio), stoi(tempsincantation), stoi(coutmana));
				}
				else {
					cout << "La ligne du fichier de chargemnet concernant la compétence " << numero << " est incomplet !" << endl;
					cout << "Impossible de charger la compétence" << endl;
					return NULL;
				}
			}
		}
		fichier.close();
		cout << "La competence numero " << numero << " n'est pas renseignée dans le fichier " << DATASAVECOMP << endl;
		return NULL;
	}
	else {
		cout << "Le fichier " << DATASAVECOMP << " est introuvable " << endl;
		return NULL;
	}
}

Joueur * ChargerJoueur(string pseudo, string nomclasse) {

	ifstream fichier(DATASAVEPLAYER, ios::in);
	string contenu;
	string lignefichier;

	if (fichier) {
		getline(fichier, contenu);
		getline(fichier, contenu);
		contenu = " ";
		while (contenu != "") {
			getline(fichier, contenu);
			lignefichier = contenu.substr(0, contenu.find("/"));
			if (nomclasse == lignefichier) { // on a trouve le Personnage qu'on cherchait

				string classe, hp, mana, armure, force, comp1, comp2, comp3, comp4;
				// recupere la ligne sans le numero de la competence

				lignefichier = contenu.substr(0, contenu.find("/"));
				classe = lignefichier;

				contenu = contenu.substr(contenu.find("/") + 1, contenu.length());
				lignefichier = contenu.substr(0, contenu.find("/"));
				hp = lignefichier;

				contenu = contenu.substr(contenu.find("/") + 1, contenu.length());
				lignefichier = contenu.substr(0, contenu.find("/"));
				mana = lignefichier;
				// ratio chargé

				contenu = contenu.substr(contenu.find("/") + 1, contenu.length());
				lignefichier = contenu.substr(0, contenu.find("/"));
				armure = lignefichier;
				//temps incantation chargé			

				contenu = contenu.substr(contenu.find("/") + 1, contenu.length());
				lignefichier = contenu.substr(0, contenu.find("/"));
				force = lignefichier;

				contenu = contenu.substr(contenu.find("/") + 1, contenu.length());
				lignefichier = contenu.substr(0, contenu.find("/"));
				comp1 = lignefichier;
				//cout mana chargé				

				contenu = contenu.substr(contenu.find("/") + 1, contenu.length());
				lignefichier = contenu.substr(0, contenu.find("/"));
				comp2 = lignefichier;

				contenu = contenu.substr(contenu.find("/") + 1, contenu.length());
				lignefichier = contenu.substr(0, contenu.find("/"));
				comp3 = lignefichier;

				contenu = contenu.substr(contenu.find("/") + 1, contenu.length());
				lignefichier = contenu.substr(0, contenu.find("/"));
				comp4 = lignefichier;

				fichier.close();

				if (classe != "" && hp != "" && mana != "" && force != "" &&  armure != "" && comp1 != "" && comp2 != "" && comp3 != "" && comp4 != "") {
					return new Joueur(pseudo, classe, stoi(hp), stoi(mana), stoi(armure), stoi(force), stoi(comp1), stoi(comp2), stoi(comp3), stoi(comp4));
				}
				else {
					cout << "La ligne du fichier de chargemnet concernant le Personnage de la classe " << nomclasse << " est incomplet !" << endl;
					cout << "Impossible de charger le Personnage" << endl;
					return NULL;
				}
			}
		}
		fichier.close();
		cout << "Le Personnage de la classe " << nomclasse << " n'est pas renseignée dans le fichier " << DATASAVEPLAYER << endl;
		return NULL;
	}
	else {
		cout << "Le fichier " << DATASAVEPLAYER << " est introuvable " << endl;
		return NULL;

	}
}



