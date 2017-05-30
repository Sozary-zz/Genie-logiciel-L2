#pragma once
#include <stack>
#include <SFML\Graphics.hpp>
#define GAME_W 800
#define GAME_H 600

class GameState;

class Game
{
public:
	Game();
	~Game();

	void pushState(GameState* state);// ajoute un nouvel etat de jeu
	void popState(); // enleve le dernier etat de jeu
	void changeState(GameState* state); // change l etat de jeu courrant
	GameState* peekState();// et le recuperer

	void gameLoop(); // standard boucle while

	std::stack<GameState*> states;
	sf::RenderWindow window;
};

