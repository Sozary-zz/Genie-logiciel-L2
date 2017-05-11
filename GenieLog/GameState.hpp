#pragma once
#include <SFML\Audio.hpp>
#include "Player.h"
#include "Monster.h"
#include "Game.hpp"
#include "TextureManager.h"
#include "FontManager.h"

#define DEFAULT_HEIGHT 15 //20 max!
#define DEFAULT_WIDTH  15
#define MAIN_VOLUME 1

class GameState
{
public:
	virtual void draw(const float delta_time) = 0;
	virtual void update(const float delta_time) = 0;
	virtual void eventLoop() = 0;

	Game* game;

	 static TextureManager* texture_manager;
	 static FontManager* font_manager;



	int width;
	int height;
};

