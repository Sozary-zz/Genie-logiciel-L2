/**
*\file Menu.h
*\brief Ce fichier gère le Menu pour voir son inventaire , quitter le jeu etc..
*\author 
*\date 06 Mai 2017
**/

#pragma once
#include <SFML\Graphics.hpp>
#include "GameState.hpp"


enum class CHOICE {PROFIL,INVENTORY,SAVE,QUIT};// elem menu selec
class Menu: public sf::Drawable
{
public:
	Menu();

	void adjustPos(sf::Vector2f size, sf::Vector2f position);// positionne menu dans fenetre de jeu
	void setVisible( bool visible);// change sa visibilité
	bool isVisible(); // est visible?
	void up();// change curseur
	void down();// change curseur
	CHOICE getChoice();// retourne choix

	~Menu();

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Sprite m_background;//fond
	sf::Text *m_texts;//textes
	sf::Sprite m_arrow;//curseur

	int m_choice;//choix courrant

	bool m_visible;//visibilité
};

