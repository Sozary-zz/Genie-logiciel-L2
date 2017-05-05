#pragma once
#include <SFML\Graphics.hpp>
#include "GameState.hpp"

enum class CHOICE {PROFIL,INVENTORY,SAVE,QUIT};
class Menu: public sf::Drawable
{
public:
	Menu();

	void adjustPos(sf::Vector2f size, sf::Vector2f position);
	void setVisible( bool visible);
	bool isVisible();
	void up();
	void down();
	CHOICE getChoice();

	~Menu();

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Sprite m_background;
	sf::Text *m_texts;
	sf::Sprite m_arrow;

	int m_choice;

	bool m_visible;
};

