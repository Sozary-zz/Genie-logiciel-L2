#pragma once
#include <string>
#include <SFML\Graphics.hpp>
#include "Exception.h"
#include "LayoutButton.h"
#include "LayoutInput.h"
#include "LayoutLabel.h"


class LayoutBase  // this is the really base of all the windows layout
{
public:
	LayoutBase(int, int, std::string, sf::Color = sf::Color(45, 45, 48)); 
	void run();
	void addComponent(LayoutComponent*);
	~LayoutBase();
private:
	sf::Color m_background_color;
private:
	sf::RenderWindow m_window;
	LayoutButton* m_submit_button;
	std::vector<LayoutComponent*> m_components; // for handle all the possible layouts


};

