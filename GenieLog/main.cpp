#include "Game.hpp"
#include "GameMenu.hpp"

TextureManager* GameState::texture_manager = new TextureManager;
FontManager* GameState::font_manager = new FontManager;

int main() {
	Game game;

	game.pushState(new GameMenu(&game));
	game.gameLoop();


	delete GameState::texture_manager;
	delete GameState::font_manager;

	return 0;
}
