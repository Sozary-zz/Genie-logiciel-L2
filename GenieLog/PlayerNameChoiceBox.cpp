#include "PlayerNameChoiceBox.h"

#include <iostream>

using namespace sf;
using namespace std;



PlayerNameChoiceBox::PlayerNameChoiceBox(int width, int height, std::string name):
	LayoutBase(width, height, name)
{
	addComponent(new LayoutLabel(
		Vector2f(5, (height / 6)),
		string("data\\GOTHIC.TTF"),
		string("Pseudo: "),
		16,
		Color(255, 255, 255),
		Color(255, 255, 255)));

	addComponent(new LayoutInput(
		Vector2f(width / 2, 25),
		Vector2f(width / 2 - 10, (height / 6)),
		INPUT_TYPE_RESTRICT::FREE));

	addComponent(new LayoutButton(
		Vector2f(90, 35),
		Vector2f(width / 4 - 45, height - 35 * 1.5),
		WISTERIA,
		bind(&PlayerNameChoiceBox::actionButton, this, placeholders::_1),
		"Créer",
		SUBMIT_BUTTON_COMPONENT));

	addComponent(new LayoutButton(
		Vector2f(90, 35),
		Vector2f(3 * (width / 4) - 45, height - 35 * 1.5),
		WISTERIA,
		bind(&PlayerNameChoiceBox::actionButton, this, placeholders::_1),
		"Annuler",
		END_BUTTON_COMPONENT));
}

void PlayerNameChoiceBox::actionButton(std::string s)
{
	if (!s.empty())
		throw s;
}
