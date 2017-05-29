#include "PlayerNameChoiceBox.h"

#include <iostream>

using namespace sf;
using namespace std;



PlayerNameChoiceBox::PlayerNameChoiceBox(int width, int height, std::string name) :
	LayoutBase(width, height, name)
{
	addComponent(new LayoutLabel(
		Vector2f(5, (height / 6)),
		string("data\\GOTHIC.TTF"),
		string("Pseudo: "),
		16,
		Color(255, 255, 255),
		Color(255, 255, 255)));

	addComponent(new LayoutLabel(
		Vector2f(5, 2 * (height / 6)),
		string("data\\GOTHIC.TTF"),
		string("Taille de la carte: "),
		16,
		Color(255, 255, 255),
		Color(255, 255, 255)));

	addComponent(new LayoutLabel(
		Vector2f(5, 3 * (height / 6)),
		string("data\\GOTHIC.TTF"),
		string("Nombre de monstres: "),
		16,
		Color(255, 255, 255),
		Color(255, 255, 255)));

	addComponent(new LayoutInput(
		Vector2f(width / 3, 25),
		Vector2f(width / 2 + 10, (height / 6)),
		INPUT_TYPE_RESTRICT::FREE));


	addComponent(new LayoutInput(
		Vector2f(width / 3, 25),
		Vector2f(width / 2 + 10, 2 * (height / 6)),
		INPUT_TYPE_RESTRICT::NUMBERS_ONLY));

	addComponent(new LayoutInput(
		Vector2f(width / 3, 25),
		Vector2f(width / 2 + 10, 3 * (height / 6)),
		INPUT_TYPE_RESTRICT::NUMBERS_ONLY));

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

	run();
}

void PlayerNameChoiceBox::actionButton(std::string s)
{
	if (!s.empty())
	{
		auto arr = stringSplit(s, '\n');
		auto test_a = stoi(arr[1]);// map size
		auto test_b = stoi(arr[0]); // monster number
		if (test_a < 5 || test_a>15)
			throw 0;

		if (test_b <= 0 || test_b > (int)(1.5f*sqrt(test_a)))
			throw 0;

		throw arr;
	}

}
