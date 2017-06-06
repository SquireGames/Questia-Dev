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

#include "QuestiaEng/TileEngine/SV_TileEngine.h"

#include "QuestiaEng/TileEngine/Tile.h"

class TileEngine
{
public:
	//ctor and dtor
	TileEngine(sf::RenderWindow& window, ResourceManager& resourceManager);
	~TileEngine();
	
	friend class TileEngine_Editor;

	void loadMap(const std::string& mapName, TileMap::TextureMode textureMode = TileMap::TextureMode::Map, TileMap::TileMode tileMode = TileMap::TileMode::Batch);
	void closeMap();

	void draw();

	void setViewportSize(float width, float height);

	void setPosition(int x, int y);
	
	bool isLoaded() {return currentMap.isLoaded();}
	
private:

	//draws chunks
	void drawMap();
	//draws separate tiles
	void drawTiles();
	
	//in charge of next map to load
	std::string nextMap = std::string();

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
