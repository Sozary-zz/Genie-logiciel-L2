#include "Menu.h"



Menu::Menu()
{
	GameState::texture_manager->addElement("menu","data\\menu.png");
	GameState::texture_manager->addElement("arrow_menu","data\\arrow.png");

}


Menu::~Menu()
{
}
void Menu::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw();
}
