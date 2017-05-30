#pragma once
#include <string>
#include <SFML\Graphics.hpp>
#include "Tools.hpp"
#include "GameState.hpp"
#include "SOZLayout\LayoutBase.h"
class PlayerNameChoiceBox :public LayoutBase
{
public:
	PlayerNameChoiceBox(int width, int height, std::string name);
private:
	void actionButton(std::string);// action quand choisi le nom
};

