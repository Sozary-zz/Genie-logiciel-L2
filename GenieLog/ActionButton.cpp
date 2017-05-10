/**
*\file ActionButton.cpp
*\brief Programmes gérant les différents evenements sur les boutons au niveau du Menu de lancement
*\author
*\date 06 Mai 2017


**/


#include "ActionButton.h"

using namespace sf;
using namespace std;

/**
*\fn ActionButton , Cette fonction est le constructeur de la class ActionButton
* Elle prend donc en argument :
*\param label le nom du bouton
*\param position la position du texte
*\param size la taille du texte
*\param bckgrnd la couleur du background
*\param font_color la couleur du texte
*\param font la police du texte
**/
ActionButton::ActionButton(const string & label, Vector2f position, Vector2f size, Color bckgrnd, Color font_color, const Font & font)
	:m_pushed(false), m_hoovered(false), m_base_font_color(font_color), m_base_main_color(bckgrnd)
{
	m_text.setString(label);/*!<Fixe le text sur le bouton */
	m_text.setFont(font);/*!<Fixe la police du text */
	m_text.setColor(font_color);/*!<Fixe la couleur du texte */
	m_text.setCharacterSize(size.y*0.5f);/*!<Fixe la taille de la police */
	m_text.setPosition(position + Vector2f(size.x / 2.f - m_text.getGlobalBounds().width / 2.f, size.y / 2.f - m_text.getGlobalBounds().height));/*!<Fixe la position du texte sur le bouton */

	m_shape.setFillColor(bckgrnd);/*!<Fixe la couleur du background du bouton */
	m_shape.setSize(size);/*!<Fixe la taille du bouton */
	m_shape.setPosition(position);/*!<Fixe la position du bouton */
}
/**
*\fn ~ActionButton , cette fonction est le destructeur de la class ActionButton
**/
ActionButton::~ActionButton()
{
}

/**
*\fn buttonPushed , cette fonction sert à savoir si on a appuyé sur un bouton
*\param[out] m_pushed variable booléenne globale , clic gauche appuyé
**/
bool ActionButton::buttonPushed() const
{
	return m_pushed;
}
/**
*\fn update , cette fonction gère les différents évenements effectués sur les boutons
*\param event Différents evenements possibles : fonction de librairie sfml
**/
void ActionButton::update(const Event & event)
{
	m_pushed = false; /*!<Initialisation de la variable "bouton appuyé" à faux */

	if (m_shape.getGlobalBounds().contains(Vector2f(event.mouseButton.x, event.mouseButton.y))/*!<Si on se trouve sur un bouton avec notre souris et qu'on appuie sur un des deux clics alors on met la variable m_pushed à true pour signifier qu'on a cliqué dessus */
		&& event.type == Event::MouseButtonPressed)
		m_pushed = true;

	if (m_shape.getGlobalBounds().contains(Vector2f(event.mouseMove.x, event.mouseMove.y))/*!<Si notre souris se trouve sur le bouton en la deplacant , on met la variable m_hovered à true pour signifier qu'on est en train de passer dessus */
		&& event.type == Event::MouseMoved)
		m_hoovered = true;
	else
		m_hoovered = false;/*!<Sinon on la laisse à false */

	if (m_hoovered) {
		if (m_shape.getFillColor().toInteger() == m_base_main_color.toInteger())/*!<Si on hoover le bouton on change legerement la couleur du bouton pour l'ergonomie */
			m_shape.setFillColor(Color(0, 102, 135));
	}

	else
		if (m_shape.getFillColor().toInteger() != m_base_main_color.toInteger())
			m_shape.setFillColor(m_base_main_color);
}
/**
*\fn setState , cette fonction définit l'état du bouton , si on passe dessus , ou qu'on a cliqué ..
*\param state l'état du bouton
**/
void ActionButton::setState(bool state)
{
	m_pushed = state;/*!<Fixe l'état du bouton */
}
/**
*\fn draw , cette fonction sert à afficher les boutons dans la fenetre SFML 
**/
void ActionButton::draw(RenderTarget & target, RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_shape);/*!< Afficher la forme du bouton */
	target.draw(m_text);/*!< Affiche le texte */
}

