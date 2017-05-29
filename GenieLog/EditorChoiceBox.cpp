#include "EditorChoiceBox.h"
#include <iostream>

using namespace sf;
using namespace std;

EditorChoiceBox::EditorChoiceBox(int width, int height, string name) :
	LayoutBase(width, height, name)
{
	addComponent(new LayoutLabel(
		Vector2f(5, (height / 6)),
		string("data\\GOTHIC.TTF"),
		string("Largeur carte: "),
		16,
		Color(255, 255, 255),
		Color(255, 255, 255)));

	addComponent(new LayoutLabel(
		Vector2f(5, 2 * (height / 6)),
		string("data\\GOTHIC.TTF"),
		string("Hauteur carte: "),
		16,
		Color(255, 255, 255),
		Color(255, 255, 255)));

	addComponent(new LayoutLabel(
		Vector2f(5, 3 * (height / 6)),
		string("data\\GOTHIC.TTF"),
		string("Nombre monstres: "),
		15,
		Color(255, 255, 255),
		Color(255, 255, 255)));

	addComponent(new LayoutInput(
		Vector2f(width / 2, 25),
		Vector2f(width / 2 - 10, (height / 6)),
		INPUT_TYPE_RESTRICT::NUMBERS_ONLY));

	addComponent(new LayoutInput(
		Vector2f(width / 2, 25),
		Vector2f(width / 2 - 10, 2 * (height / 6)),
		INPUT_TYPE_RESTRICT::NUMBERS_ONLY));

	addComponent(new LayoutInput(
		Vector2f(width / 2, 25),
		Vector2f(width / 2 - 10, 3 * (height / 6)),
		INPUT_TYPE_RESTRICT::NUMBERS_ONLY));

	addComponent(new LayoutButton(
		Vector2f(90, 35),
		Vector2f(width / 4 - 45, height - 35 * 1.5),
		WISTERIA,
		bind(&EditorChoiceBox::actionButton, this, placeholders::_1),
		"Créer",
		SUBMIT_BUTTON_COMPONENT));

	addComponent(new LayoutButton(
		Vector2f(90, 35),
		Vector2f(3 * (width / 4) - 45, height - 35 * 1.5),
		WISTERIA,
		bind(&EditorChoiceBox::actionButton, this, placeholders::_1),
		"Annuler",
		END_BUTTON_COMPONENT));

	run();
}

void EditorChoiceBox::actionButton(string s)
{

	if (!s.empty())
	{
		auto splitted_string = stringSplit(s, '\n');

		if (splitted_string.size() == 3) {
			if (splitted_string[2].empty() || stoi(splitted_string[2]) < 5 || stoi(splitted_string[2]) >= 15)
				throw 0x0;

			if (splitted_string[1].empty() || stoi(splitted_string[1]) < 5 || stoi(splitted_string[1]) >= 15)
				throw 0x0;

			if (splitted_string[0].empty() || stoi(splitted_string[0]) < 2 || stoi(splitted_string[0]) >= (int)sqrt(15*15))
				throw 0x0;
			throw splitted_string;
		}		
	}
}


