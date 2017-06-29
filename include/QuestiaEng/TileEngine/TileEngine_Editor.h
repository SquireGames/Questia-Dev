#ifndef TILEENGINE_EDITOR_H
#define TILEENGINE_EDITOR_H

#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "QuestiaEng/TileEngine/TileEngine.h"
#include "QuestiaEng/ResourceManager/ResourceManager.h"

#include "QuestiaEng/Utl/Utl.h"

#include "QuestiaEng/TileEngine/SV_TileEngine.h"

//TODO Add undo/redo
//TODO Add resize
//TODO Add copy + paste

class TileEngine_Editor
{
public:
	//ctor + dtor
	TileEngine_Editor(sf::RenderWindow& window, ResourceManager& resourceManager, TileEngine& tileEng);
	~TileEngine_Editor() = default;

	void createMap(const std::string& mapName, unsigned int width, unsigned int height, unsigned int layers);
	void closeMap();
	
	void setViewportSize(float width, float height) {tileEngine.setViewportSize(width, height);}
	void setPosition(int x, int y);
	bool isLoaded() {return tileEngine.isLoaded();}

	///gets called instead of base class
	void loadMap(const std::string& mapName);
	//draws map with sprites
	void draw();
	//draws out all tiles
	void drawTiles(sf::Font& font);
	//only draws specific layers (transparency out of 100)
	void drawLayer(int layer, int transparency);

	//saves map
	void overrideMap();

	void showGridLines(bool gridLinesVisible) {isGridDrawn = gridLinesVisible;}
	void showBorderMaps(bool gridMapVisible)  {areBordersDrawn = gridMapVisible;}

	//reset transparency
	void resetTileAlpha();

	//get map data
	unsigned int getMapWidth();
	unsigned int getMapHeight();
	unsigned int getMapLayers();

	//hover over
	void hoverTile(int x, int y);
	void hoverSpan(int x, int y, int size_x, int size_y);

	//grid to know where invisible tiles are
	void drawGridLines();

	//gets current tile or returns a nullptr
	Tile* getTile_tileState(int x, int y);
	int getTileID(const std::string& source);

	void replaceTile(int newTile, int x, int y, int layer);
	
	//border map editing
	void changeBorderMap(utl::Direction dir, const std::string& mapName);
	void changeBorderOffset(utl::Direction dir, int offset);

	//for 'save as' functionality
	void changeMapName(const std::string& newName);
	
	//debugging
	//prints all tiles and folders into consolse
	void printTiles();

private:
	//gets all tiles in a folder
	std::pair<std::string, std::vector<Tile*> >& getFolder(const std::string& dir);

	sf::RenderWindow& window;
	ResourceManager& resourceManager;
	TileEngine& tileEngine;

	//stores all tiles for drawing
	std::vector<std::pair<std::string, std::vector<Tile*>>> sortedTiles;

	sf::VertexArray gridLines;
	
	SV_TileEngine saveFile;
	
	bool isGridDrawn = true;	
	bool areBordersDrawn = true;	
};

#endif // TILEENGINE_EDITOR_H
