#include "Menu.h"

using namespace std;
using namespace sf;

Menu::Menu() :m_choice(0)
{
	GameState::texture_manager->addElement("menu", "data\\menu.png");
	GameState::texture_manager->addElement("arrow_menu", "data\\arrow.png");


	m_arrow.setTexture(GameState::texture_manager->getElement("arrow_menu"));
	m_background.setTexture(GameState::texture_manager->getElement("menu"));

	m_texts = new Text[4];

	m_texts[0].setString("Profil");
	m_texts[1].setString("Sac");
	m_texts[2].setString("Sauvegarder");
	m_texts[3].setString("Quitter");

	for (int i = 0; i < 4; ++i)
	{
		m_texts[i].setFont(GameState::font_manager->getElement("main_font"));
		m_texts[i].setColor(Color::Black);
		m_texts[i].setCharacterSize(20);
	}


}


void Menu::adjustPos(sf::Vector2f size, sf::Vector2f position)
{
	m_background.setPosition(position);
	m_background.setScale(size.x / m_background.getTexture()->getSize().x, size.y / m_background.getTexture()->getSize().y);

	m_arrow.setPosition({ position.x + 20,position.y + 43 + 32 * m_choice });
	m_arrow.scale(10.f / m_arrow.getTexture()->getSize().x, 20.f / m_arrow.getTexture()->getSize().y);
	for (int i = 0; i < 4; ++i)
		m_texts[i].setPosition({ position.x + 40,position.y + 32 * i + 40 });
}

void Menu::setVisible(bool visible)
{
	if (m_visible != visible)
	{
		m_choice = 0;
		auto position = m_background.getPosition();
		m_arrow.setPosition({ position.x + 20,position.y + 43 + 32 * m_choice });
	}
	
	m_visible = visible;
}

bool Menu::isVisible()
{
	return m_visible;
}

void Menu::up()
{
	if (m_choice > 0)
	{
		auto position = m_background.getPosition();
		m_arrow.setPosition({ position.x + 20,position.y + 43 + 32 * --m_choice });
	}
}

void Menu::down()
{
	if (m_choice < 3)
	{
		auto position = m_background.getPosition();
		m_arrow.setPosition({ position.x + 20,position.y + 43 + 32 * ++m_choice });
	}
}

CHOICE Menu::getChoice()
{
	switch (m_choice)
	{
	case 0:return CHOICE::PROFIL;
	case 1:return CHOICE::INVENTORY;
	case 2:return CHOICE::SAVE;
	case 3:return CHOICE::QUIT;
	}
	
}

Menu::~Menu()
{
	delete[] m_texts;
}
void Menu::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_background);
	target.draw(m_arrow);
	for (int i = 0; i < 4; ++i)
		target.draw(m_texts[i]);
}
