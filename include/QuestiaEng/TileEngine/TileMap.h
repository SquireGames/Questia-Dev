#ifndef TILEMAP_H
#define TILEMAP_H

#include <map>

#include "QuestiaEng/TileEngine/Tile.h"

class TileMap
{
public:
	TileMap();
	~TileMap();

	enum class TextureMode  {Map, All};
	enum class TileMode     {Sprite, Batch};

	bool fixMapData() {isMapDataSet = true;}
	bool initialize(TextureMode textureMode, TileMode tileMode) {isInitialized = true;}
	
	void setTileMap(std::vector <int> p_tileMap)		{ if(!isInitialized) {tileMap = p_tileMap;}}
	void setTileKey(std::map <int, Tile> p_tileKey)		{ if(!isInitialized) {tileKey = p_tileKey;}}
	void setWidth(unsigned int p_width) 				{ if(!isInitialized) {width = p_width;}}
	void setHeight(unsigned int p_height)				{ if(!isInitialized) {height = p_height;}}
	void setLayers(unsigned int p_layers) 				{ if(!isInitialized) {layers = p_layers;}}
	void setMaxTileSize_x(unsigned int p_maxTileSize_x) { if(!isInitialized) {maxTileSize_x = p_maxTileSize_x;}}
	void setMaxTileSize_y(unsigned int p_maxTileSize_y) { if(!isInitialized) {maxTileSize_y = p_maxTileSize_y;}}
	
	std::vector <int>& getTileMap() 	{return tileMap;}
	std::map <int, Tile>& getTileKey() 	{return tileKey;}
	unsigned int getWidth() 			{return width;}
	unsigned int getHeight() 			{return height;}
	unsigned int getLayers() 			{return layers;}
	unsigned int getMaxTileSize_x() 	{return maxTileSize_x;}
	unsigned int getMaxTileSize_y() 	{return maxTileSize_y;}

private:
	//dimensions
	unsigned int width = 0, height = 0, layers = 0;
	//biggest sized tile dimensions
	unsigned int maxTileSize_x = 0, maxTileSize_y = 0;
	
	//once map set, not modifyable
	bool isMapDataSet = false;
	//once initilized, non-modifyable mode
	bool isInitialized = false;
	
	// (width * height * layers) sized vector, holds tile ID
	std::vector <int> tileMap;
	// pass tileID, get Tile
	std::map <int, Tile> tileKey;
};

#endif // TILEMAP_H
