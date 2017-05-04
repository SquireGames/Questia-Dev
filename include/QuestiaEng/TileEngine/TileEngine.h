#ifndef TILEENGINE_H
#define TILEENGINE_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>
#include <vector>
#include <utility>
#include <map>
#include <cmath>    //std::floor

#include "QuestiaEng/TileEngine/TileMap.h"

#include "QuestiaEng/ResourceManager/ResourceManager.h"

#include "QuestiaEng/Utl/Utl.h"
#include "QuestiaEng/Utl/SpriteSheet.h"

#include "QuestiaEng/TileEngine/SaveFile_TileEngine.h"
#include "QuestiaEng/TileEngine/SaveFile_TileEngine.h"

#include "QuestiaEng/TileEngine/Tile.h"

class TileEngine
{
public:
	//ctor and dtor
	TileEngine(sf::RenderWindow& _window, ResourceManager& _resourceManager);
	~TileEngine();

	void loadMap(std::string _mapName, TileMap::TextureMode textureMode, TileMap::TileMode tileMode);
	void closeMap();

	void draw();

	void setViewportSize(float width, float height);

	//set tiles drawn from player position
	void setPosition(int x, int y);
protected:
	//draws chunks
	void drawMap();
	//draws separate tiles
	void drawTiles();

	//tiles fit on screen
	unsigned int tileFit_x = (1920.f / 64.f) + 2; // +2 for transitioning tiles
	unsigned int tileFit_y = (1080.f / 64.f) + 2; // +2 for transitioning tiles
	
	utl::Vector2i cameraPosition {utl::Vector2i(0,0)};

	///helpers
	//for map
	int getTile(unsigned int x, unsigned int y, unsigned int layer);
	int getChunk(unsigned int x, unsigned int y, unsigned int layer);

	///default
	sf::RenderWindow& window;
	ResourceManager& resourceManager;

	//holds map
	TileMap currentMap;
};

#endif // TILEENGINE_H
