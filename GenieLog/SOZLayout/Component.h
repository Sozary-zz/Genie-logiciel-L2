#pragma once
#include <SFML\Graphics.hpp>
#include <string>

#define BUTTON_COMPONENT        0x1
#define SUBMIT_BUTTON_COMPONENT 0x2
#define INPUT_COMPONENT         0x3
#define LABEL_COMPONENT			0x4
#define END_BUTTON_COMPONENT    0x5
#define FINISH_BUTTON_STATE     0x6

class LayoutComponent :public sf::Drawable { // each component can be defined
public:
	LayoutComponent() {};
	virtual int getComponent() const = 0; // by his id
	virtual void update(sf::Event, std::string&) = 0; // by his update function
	virtual std::string getString() const = 0; // and more specifically by his string
};