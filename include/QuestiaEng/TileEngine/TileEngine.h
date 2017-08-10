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

#include <unordered_map>

#include "QuestiaEng/TileEngine/TileMap.h"

#include "QuestiaEng/ResourceManager/ResourceManager.h"

#include "QuestiaEng/Utl/Utl.h"
#include "QuestiaEng/Utl/SpriteSheet.h"

#include "QuestiaEng/TileEngine/SV_TileEngine.h"

#include "QuestiaEng/TileEngine/Tile.h"

class TileEngine
{
public:
	//for client
	TileEngine(sf::RenderWindow& window, ResourceManager& resourceManager);
	//for server
	TileEngine();

	~TileEngine() = default;

	//only needs to be called to change default settings
	void setMode(TileMap::TextureMode textureMode, TileMap::RenderMode renderMode);

	//loads map and textures
	void loadMap(const std::string& mapName);

	//just loads map data
	//TODO implement
	void loadMapData();

	void closeMap(const std::string& mapName);
	void closeMap(int mapID);
	void closeMaps();

	//draws the surrounding maps if visible (9 maximum)
	void draw();

	void setViewportSize(float width, float height);
	void setPosition(utl::Vector2f& pos);

	bool isLoaded() {return maps.size();}

private:
	//draws single map
	void drawMap(TileMap* map, utl::Direction dir, TileMap* refMap = nullptr, int tilesOffset = 0, int otherAxisOffset = 0);

	int getTile(unsigned int x, unsigned int y, unsigned int layer, TileMap* map);
	int getChunk(unsigned int x, unsigned int y, unsigned int layer, TileMap* map);

	//tiles fit on screen
	unsigned int tileFit_x = (1920.f / 64.f) + 2; // +2 for transitioning tiles
	unsigned int tileFit_y = (1080.f / 64.f) + 2; // +2 for transitioning tiles

	utl::Vector2f cameraPosition {utl::Vector2f(0,0)};
	TileMap::TextureMode textureMode = TileMap::TextureMode::Map;
	TileMap::RenderMode renderMode = TileMap::RenderMode::Batch;

	sf::RenderWindow* window;
	ResourceManager* resourceManager;

	//every map is generated an ID, derived from mapCount
	std::unordered_map<std::string, int> mapID;
	std::vector<int> activeMaps;
	std::vector<TileMap> maps;
	//used to allow functions to remain void
	TileMap* lastMap = nullptr;

	int mapCount = 0;
	int currentMapID = -1;

	//used by TileEngine_Editor to only draw specific layers at a specific transparency
	//only utilized in TileMap::RenderMode::Sprite
	int layerSelection = -1;
	//transparency out of 100
	int layerTransparency = -1;

	//client - true, server - false
#ifdef DEBUGMODE
	bool displayTextures;
#endif

	bool mapLoaded(const std::string& mapName)
	{
		return mapID.count(mapName) && std::find(activeMaps.begin(), activeMaps.end(), mapID.at(mapName)) != activeMaps.end();
	}
	TileMap* getMap(const std::string& mapName)
	{
		return mapLoaded(mapName) ? getMap(mapID.at(mapName)) : nullptr;
	}
	TileMap* getMap(int mapID)
	{
		for(auto& map : maps)
		{
			if(map.getID() == mapID)
			{
				return &map;
			}
		}
		return nullptr;
	}
	//used to move camera without changing maps
	void setCamera(utl::Vector2f pos)
	{
		cameraPosition = pos;
	}
	friend class TileEngine_Editor;
};

#endif // TILEENGINE_H
