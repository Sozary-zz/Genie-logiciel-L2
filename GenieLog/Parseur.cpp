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
				char compvalide = 'o';
				string nom;
				string damages, ratio, tempsincantation, coutmana;

				// recupere la ligne sans le numero de la competence
				contenu = contenu.substr(contenu.find("/") + 1, contenu.length());
				lignefichier = contenu.substr(0, contenu.find("/"));
				nom = lignefichier;
				// nom chargé

				contenu = contenu.substr(contenu.find("/") + 1, contenu.length());
				lignefichier = contenu.substr(0, contenu.find("/"));
				nombrePossible(lignefichier, compvalide, 'c');
				damages = lignefichier;
				// damages chargés

				contenu = contenu.substr(contenu.find("/") + 1, contenu.length());
				lignefichier = contenu.substr(0, contenu.find("/"));
				nombrePossible(lignefichier, compvalide, 'c');
				ratio = lignefichier;
				// ratio chargé

				contenu = contenu.substr(contenu.find("/") + 1, contenu.length());
				lignefichier = contenu.substr(0, contenu.find("/"));
				nombrePossible(lignefichier, compvalide, 'c');
				tempsincantation = lignefichier;
				//temps incantation chargé

				contenu = contenu.substr(contenu.find("/") + 1, contenu.length());
				lignefichier = contenu.substr(0, contenu.find("/"));
				nombrePossible(lignefichier, compvalide, 'c');
				coutmana = lignefichier;
				//cout mana chargé				

				fichier.close();
				if (compvalide == 'o') {
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

				char classevalide = 'o';
				string classe, hp, mana, armure, force, comp1, comp2, comp3, comp4;
				// recupere la ligne sans le numero de la competence


				classe = lignefichier;
				//classe chargée

				contenu = contenu.substr(contenu.find("/") + 1, contenu.length());
				lignefichier = contenu.substr(0, contenu.find("/"));
				nombrePossible(lignefichier, classevalide, 'j');
				hp = lignefichier;
				//hp chargées

				contenu = contenu.substr(contenu.find("/") + 1, contenu.length());
				lignefichier = contenu.substr(0, contenu.find("/"));
				nombrePossible(lignefichier, classevalide, 'j');
				mana = lignefichier;
				// mana chargé

				contenu = contenu.substr(contenu.find("/") + 1, contenu.length());
				lignefichier = contenu.substr(0, contenu.find("/"));
				nombrePossible(lignefichier, classevalide, 'j');
				armure = lignefichier;
				//armure chargé			

				contenu = contenu.substr(contenu.find("/") + 1, contenu.length());
				lignefichier = contenu.substr(0, contenu.find("/"));
				nombrePossible(lignefichier, classevalide, 'j');
				force = lignefichier;
				//force chargée

				contenu = contenu.substr(contenu.find("/") + 1, contenu.length());
				lignefichier = contenu.substr(0, contenu.find("/"));
				nombrePossible(lignefichier, classevalide, 'j');
				comp1 = lignefichier;
				//competence 1 chargée				

				contenu = contenu.substr(contenu.find("/") + 1, contenu.length());
				lignefichier = contenu.substr(0, contenu.find("/"));
				nombrePossible(lignefichier, classevalide, 'j');
				comp2 = lignefichier;
				// competence 2 chargée

				contenu = contenu.substr(contenu.find("/") + 1, contenu.length());
				lignefichier = contenu.substr(0, contenu.find("/"));
				nombrePossible(lignefichier, classevalide, 'j');
				comp3 = lignefichier;
				//competence 3 chargée

				contenu = contenu.substr(contenu.find("/") + 1, contenu.length());
				lignefichier = contenu.substr(0, contenu.find("/"));
				nombrePossible(lignefichier, classevalide, 'j');
				comp4 = lignefichier;
				//competence 4 chargée

				fichier.close();

				if (classevalide == 'o') {
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

Monstre * ChargerMonstre(string pseudo) {
	ifstream fichier(DATASAVEMONSTER, ios::in);
	string contenu;
	string lignefichier;
	if (fichier) {
		getline(fichier, contenu);
		getline(fichier, contenu);
		contenu = " ";
		while (contenu != "") {
			getline(fichier, contenu);
			lignefichier = contenu.substr(0, contenu.find("/"));
			if (pseudo == lignefichier) { // on a trouve le Personnage qu'on cherchait
				char Pseudovalide = 'o';
				string hp, mana, armure, force, comp1, comp2, comp3, comp4;
				// recupere la ligne sans le numero de la competence

			
				pseudo = lignefichier;
				//pseudo chargée

				contenu = contenu.substr(contenu.find("/") + 1, contenu.length());
				lignefichier = contenu.substr(0, contenu.find("/"));
				nombrePossible(lignefichier, Pseudovalide, 'm');
				hp = lignefichier;
				//hp chargées

				contenu = contenu.substr(contenu.find("/") + 1, contenu.length());
				lignefichier = contenu.substr(0, contenu.find("/"));
				nombrePossible(lignefichier, Pseudovalide, 'm');
				mana = lignefichier;
				// mana chargé

				contenu = contenu.substr(contenu.find("/") + 1, contenu.length());
				lignefichier = contenu.substr(0, contenu.find("/"));
				nombrePossible(lignefichier, Pseudovalide, 'm');
				armure = lignefichier;
				//armure chargé			

				contenu = contenu.substr(contenu.find("/") + 1, contenu.length());
				lignefichier = contenu.substr(0, contenu.find("/"));
				nombrePossible(lignefichier, Pseudovalide, 'm');
				force = lignefichier;
				//force chargée

				contenu = contenu.substr(contenu.find("/") + 1, contenu.length());
				lignefichier = contenu.substr(0, contenu.find("/"));
				nombrePossible(lignefichier, Pseudovalide, 'm');
				comp1 = lignefichier;
				//competence 1 chargée				

				contenu = contenu.substr(contenu.find("/") + 1, contenu.length());
				lignefichier = contenu.substr(0, contenu.find("/"));
				nombrePossible(lignefichier, Pseudovalide, 'm');
				comp2 = lignefichier;
				// competence 2 chargée

				contenu = contenu.substr(contenu.find("/") + 1, contenu.length());
				lignefichier = contenu.substr(0, contenu.find("/"));
				nombrePossible(lignefichier, Pseudovalide, 'm');
				comp3 = lignefichier;
				//competence 3 chargée

				contenu = contenu.substr(contenu.find("/") + 1, contenu.length());
				lignefichier = contenu.substr(0, contenu.find("/"));
				nombrePossible(lignefichier, Pseudovalide, 'm');
				comp4 = lignefichier;
				//competence 4 chargée

				fichier.close();

				if (Pseudovalide == 'o' && pseudo != "") {
					return  new Monstre(pseudo, stoi(hp), stoi(mana), stoi(armure), stoi(force), stoi(comp1), stoi(comp2), stoi(comp3), stoi(comp4));
				}
				else {
					cout << "La ligne du fichier de chargemnet concernant le Monstre du nom " << pseudo << " est incomplet !" << endl;
					cout << "Impossible de charger le Monstre" << endl;
					return NULL;
				}
			}
		}
		fichier.close();
		cout << "Le Monstre du nom de " << pseudo << " n'est pas renseignée dans le fichier " << DATASAVEMONSTER << endl;
		return NULL;
	}
	else {
		cout << "Le fichier " << DATASAVEMONSTER << " est introuvable " << endl;
		return NULL;

	}
}
void nombrePossible(string contenu, char& classecomplete, char type) {
	if (classecomplete != 'n') {
		char complet = 'o';
		if (contenu == "") {
			complet = 'n';
			if (type == 'm') {
				cout << "Erreur le fichier de chargement du Monstre est mal construit ou incomplet" << endl;
			}
			if (type == 'c') {
				cout << "Erreur le fichier de chargement des Compétence est mal construit ou incomplet" << endl;
			}
			if (type == 'j') {
				cout << "Erreur le fichier de chargement du Joueur est mal construit ou incomplet" << endl;
			}
		}
		else {
			int contenuint = stoi(contenu);
			if (contenuint < 0) {
				complet = 'n';
				if (type == 'j') {
					cout << "Erreur le fichier de chargement du Joueur contient une valeur négative" << endl;
				}
				if (type == 'm') {
					cout << "Erreur le fichier de chargement du Monstre contient une valeur négative" << endl;
				}
				if (type == 'c') {
					cout << "Erreur le fichier de chargement de Competence contient une valeur négative" << endl;
				}
			}
			else if (contenuint > 1000) {
				complet = 'n';
				if (type == 'j') {
					cout << "Erreur le fichier de chargement du Joueur contient une valeur négative" << endl;
				}
				if (type == 'm') {
					cout << "Erreur le fichier de chargement du Monstre contient une valeur négative" << endl;
				}
				if (type == 'c') {
					cout << "Erreur le fichier de chargement de Competence contient une valeur négative" << endl;
				}
			}
		}
		complet = classecomplete;
	}
}

