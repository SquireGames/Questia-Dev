#ifndef TILEENGINE_EDITOR_H
#define TILEENGINE_EDITOR_H

#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "QuestiaEng/TileEngine/TileEngine.h"
#include "QuestiaEng/ResourceManager/ResourceManager.h"

#include "QuestiaEng/Utl/Utl.h"

#include "QuestiaEng/TileEngine/SaveFile_TileEngine.h"

class TileEngine_Editor : public TileEngine
{
public:
    //ctor + dtor
    TileEngine_Editor(sf::RenderWindow& _window, ResourceManager& _resourceManager);
    ~TileEngine_Editor() = default;

    void createMap(std::string mapName, unsigned int width, unsigned int height, unsigned int layers);

    ///gets called instead of base class
    void loadMap(std::string _mapName);
    //draws map with sprites
    void drawMap();
    //draws out all tiles
    void drawTiles(sf::Font& font);
    //only draws specific layers (transparency out of 100)
    void drawLayer(int layer, int transparency);

    //saves map
    void overrideMap();

    void showGridLines(bool gridLinesVisible);

    //reset transparency
    void resetTileAlpha();

    //get map data
    unsigned int getMapWidth();
    unsigned int getMapHeight();
    unsigned int getMapLayers();

    //debugging
    void displayTiles();

    //hover over
    void hoverTile(int x, int y);
    void hoverSpan(int x, int y, int size_x, int size_y);

    //grid to know where invisible tiles are
    void drawGridLines();

    //gets current tile or returns a nullptr
    Tile* getTile_tileState(int x, int y);
    int getTileID(const std::string& source);

    void replaceTile(int newTile, int x, int y, int layer);

    //for 'save as' functionality
    void changeMapName(std::string newName);

private:
	SaveFile_TileEngine saveFile;

    //stores all tiles for drawing
    std::vector<std::pair<std::string, std::vector<Tile*> > > sortedTiles;

    //grid
    sf::VertexArray gridLines;

    //save
    //SaveFile_TileEngine saveFile;

    //helpers
    std::pair<std::string, std::vector<Tile*> >& getFolder(const std::string& dir);
};

#endif // TILEENGINE_EDITOR_H
