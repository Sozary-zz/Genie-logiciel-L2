#pragma once
#include <SFML\Audio.hpp>
#include "Player.h"
#include "Monster.h"
#include "Game.hpp"
#include "TextureManager.h"
#include "FontManager.h"

#define MAIN_VOLUME 10


class GameState
{
public:
	virtual void draw(const float delta_time) = 0;//affiche
	virtual void update(const float delta_time) = 0;//met a jour
	virtual void eventLoop() = 0;// boucle eventt

	Game* game;

	 static TextureManager* texture_manager;// gestionnaire textures
	 static FontManager* font_manager;// gestionnarie font



	int width;
	int height;
};

