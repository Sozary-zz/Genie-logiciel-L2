/**
* \file ActionButton.h
* \author 
* \date 06 Mai 2017
* \brief La classe ActionButton définit les caractéristiques des boutons du menu au lancement
**/


#pragma once
#include <SFML\Graphics.hpp>
#include <string>

/**
*\class ActionButton: public sf::Drawable , public sf::Transformable
**/
class ActionButton: public sf::Drawable, public sf::Transformable /*!Elle est de type Drawable pour pouvoir l'afficher et Transformable pour pouvoir la redimentionner*/
{
public:
	ActionButton(const std::string& label, sf::Vector2f position, sf::Vector2f size, sf::Color bckgrnd, sf::Color font_color,const sf::Font &font);/*!<Constructeur prenant en argument ce qui est écris dans le bouton , sa position , sa taille , sa couleur d'arrière plan , la couleur du texte */
	~ActionButton();/*!<Destructeur */

	bool buttonPushed() const; /*!<Fonction qui permet de savoir si l'utilisateur a appuyé sur un bouton */

	void update(const sf::Event& event);/*!<Gère les appuies claviers , les différents évenements qui peut se passer */
	void setState(bool state);

private:
	bool m_pushed; /*!<Bouton pressé ? True/False */
	bool m_hoovered; /*!<Souris sur le bouton */

	sf::RectangleShape m_shape;/*!<Forme du bouton de type Rectangle de la librairie SFML */
	sf::Text m_text;/*!<Text écris sur le bouton */

	sf::Color m_base_main_color;/*!<Couleur arriere plan */
	sf::Color m_base_font_color;/*!<Couleur du texte */

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

