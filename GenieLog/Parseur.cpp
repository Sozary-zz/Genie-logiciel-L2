/**
*
*\file Parseur.cpp
*\brief Fonction qui lie le code et les fichiers text de sauvegarde
*\details Fonctions permettant de faire le lien entre Monstre,Personnage et Competence du Programme avec les fichiers dans /data/loading
*\author Nocera L.
*
*/

#include "Parseur.hpp"

/**
* \fn Competence *  ChargerCompetence(int numero) 
*\param[in] numero Numero de la compétence dans /data/loading/Competence.txt.
*\param[out] newCompetence renvoi une competence chargée via le fichier texte NULL si incomplet/aucune competence correspond au numero entre en parametre
*/
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
			lignefichier = contenu.substr(0, contenu.find("/")); // recupere la chaine de cartere entre le début de contenu jusqu'au premier '/' exclus
			if (compnumber == lignefichier) { // on a trouve la competence qu'on cherchait
				char compvalide = 'o';
				string nom;
				string damages, ratio, tempsincantation, coutmana;

				// recupere la ligne sans le numero de la competence
				contenu = contenu.substr(contenu.find("/") + 1, contenu.length()); // decoupe contenu du caractere apres le premier '/' trouvé jusqu'a la fin
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
					return new Competence(nom, stoi(damages), stoi(ratio), stoi(tempsincantation), stoi(coutmana)); /*! Appele le constructeur de Competence si compvalide == 'o' */
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

/**
*\fn Joueur * ChargerJoueur(string pseudo, string nomclasse)
*\param nomclasse Nom de la classe du Personnage dans /data/loading/Player.txt
*\param pseudo Pseudo rentré par l'utilisateur
*\param[out] newJoueur Renvoi un Joueur chargé via le fichier texte. NULL si incomplet/nomclasse pas trouvé
*/

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
			lignefichier = contenu.substr(0, contenu.find("/")); // recupere la chaine de cartere entre le début de contenu jusqu'au premier '/' exclus

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
					if(pseudo != ""){
						return new Joueur(pseudo, classe, stoi(hp), stoi(mana), stoi(armure), stoi(force), stoi(comp1), stoi(comp2), stoi(comp3), stoi(comp4));/*! Appele le constructeur de Joueur si classevalide == 'o' */
					}
					else{
						cout << "La fonction ChargerPersonnage a été mal appelée avec un pseudo vide pour le joueur" << endl;
					}
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

/**
*\fn ChargerMonstre retourne un Monstre lu dans le fichier /data/loading/Monster.txt
*\param[in] pseudo Nom du monstre dans /data/loading/Monster.txt
*\param[out] newMonstre reenvoi un Monstre chargé via le fichier teste. NULL si incomplet/pseudo correspondant a aucun monstre
*/

Monstre * ChargerMonstre(string pseudo){
	ifstream fichier(DATASAVEMONSTER, ios::in);
	string contenu;
	string lignefichier;
	if (fichier) {
		getline(fichier, contenu);
		getline(fichier, contenu);
		contenu = " ";
		while (contenu != "") {
			getline(fichier, contenu);
			lignefichier = contenu.substr(0, contenu.find("/")); // recupere la chaine de cartere entre le début de contenu jusqu'au premier '/' exclus
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
					return  new Monstre(pseudo, stoi(hp), stoi(mana), stoi(armure), stoi(force), stoi(comp1), stoi(comp2), stoi(comp3), stoi(comp4));/*! Appele le constructeur de Monstre si Pseudovalide == 'o' */
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

/**
*\fn void nombrePossible(string contenu, char& classecomplete, char type)
*\brief retourne un Monstre lu dans le fichier /data/loading/Monster.txt
*\param[in] contenu Chaine de caractère a analyser
*\param[in] classecomplete Vaut 'o' si le chargement des parametres precedent est complet et 'n' si il y a une erreur
*\param[in] type Indique quel type de Parseur appelle la fonction pour préciser a l'utilisateur quel fichier est mal renseigné 
*\parblock
* type si type = 'c' il s'agit d'une competence, si type = 'm' il s'agit d'un mosntre, si type = 'j' il s'agit d'un joueur
*\endparblock
*/
void nombrePossible(string contenu, char& classecomplete, char type) {
	if (classecomplete != 'n') { /*!<Es ce que la classe est déja incomplete ? */
/*!< */
		char complet = 'o';
		if (contenu == "") { /*!< Gere Si la chaine est vide */
			complet = 'n';
			/*!< Ecrit en un message d'erreur en fonction de la fonction qui a appelé nombrePossible */
			if (type == 'm') { /
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
			int contenuint = stoi(contenu); // On le transforme maintenant en int (il représente biensur un int alloué en string) afin d'effectuer d'autres test
			if (contenuint < 0) { : /*<Gere si la valeur est nulle */
				complet = 'n';
				// Ecrit en un message d'erreur en fonction de la fonction qui a appelé nombrePossible 
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
			else if (contenuint > NOMBREMAX) { /*< On gere Si la valeur est trop grande */
				complet = 'n';
				// Ecrit en un message d'erreur en fonction de la fonction qui a appelé nombrePossible
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
		/*! < Met a jour classeomplete si elle était complete pour savoir si le nombre chargé est "possible" */
		/*! < Soit non null, non négatif et pas superieur a NOMBREMAX ( defini dans Parseur.hpp ) */
		complet = classecomplete;
	}
}
