#pragma once
#include <string>
#include <SFML\Graphics.hpp>
#include "Tools.hpp"
#include "GameState.hpp"
#include "SOZLayout\LayoutBase.h"

class EditorChoiceBox:public LayoutBase
{
public:
	EditorChoiceBox(int width, int height, std::string name);

private:
	void actionButton(std::string);
};
