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

#include "QuestiaEng/Data/Data_Desktop.h"
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

    //draws chunks
    void drawMap();
    //draws separate tiles
    void drawTiles();

    void setViewportSize(float width, float height);

    //set tiles drawn from player position
    void setPosition(int x, int y);

    //collision detection
    //utl::Direction

protected:
    ///map
    //stores tiles
    std::map <int, Tile> tileStorage;

    //stores map
    std::vector <int> tileMap;
    //stores map dimensions
    unsigned int mapWidth = 0, mapHeight = 0, mapLayers = 0;
    //largest tile in map for tile culling
    unsigned int maxTileSize_x = 1, maxTileSize_y = 1;

    //tiles fit on screen
    unsigned int tileFit_x = (1920.f / 64.f) + 2; // +2 for transitioning tiles
    unsigned int tileFit_y = (1080.f / 64.f) + 2; // +2 for transitioning tiles

    ///data
    utl::Vector2i cameraPosition {utl::Vector2i(0,0)};
    SaveFile_TileEngine saveFile;
    std::string mapName = "nil";

    ///helpers
    //for map
    int getTile(unsigned int x, unsigned int y, unsigned int layer);
    int getChunk(unsigned int x, unsigned int y, unsigned int layer);

    ///default
    sf::RenderWindow &window;
    ResourceManager& resourceManager;

    ///chunk renderer
    //chunk size is 8x8 tiles
    std::vector <sf::VertexArray> chunkVector;
    //chunks
    unsigned int chunks_x = 0, chunks_y = 0;
    //texture
    sf::Texture* textureAtlas = nullptr;
};

#endif // TILEENGINE_H
