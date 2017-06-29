#ifndef TILEMAP_H
#define TILEMAP_H

#include <map>

#include "QuestiaEng/TileEngine/Tile.h"

class TileMap
{
public:
	TileMap() = default;
	~TileMap() = default;

	enum class TextureMode {Map, All} textureMode				= TextureMode::Map;
	enum class RenderMode  {Sprite, Batch, Unloaded} tileMode	= RenderMode::Batch;

	void initialize() {isInitialized = true;}

	void setName(const std::string& name)				{ if(!isInitialized) {tileMapName = name;}}
	void setID(int id)									{ if(!isInitialized) {this->id = id;}}
	void setTileMap(std::vector <int> p_tileMap)		{ if(!isInitialized) {tileMap = p_tileMap;}}
	void setTileKey(std::map <int, Tile> p_tileKey)		{ if(!isInitialized) {tileKey = p_tileKey;}}
	void setWidth(unsigned int p_width) 				{ if(!isInitialized) {width = p_width;}}
	void setHeight(unsigned int p_height)				{ if(!isInitialized) {height = p_height;}}
	void setLayers(unsigned int p_layers) 				{ if(!isInitialized) {layers = p_layers;}}
	void setMaxTileSize_x(unsigned int p_maxTileSize_x) { if(!isInitialized) {maxTileSize_x = p_maxTileSize_x;}}
	void setMaxTileSize_y(unsigned int p_maxTileSize_y) { if(!isInitialized) {maxTileSize_y = p_maxTileSize_y;}}
	void setTextureMode(TextureMode mode)				{ if(!isInitialized) {textureMode = mode;}}
	void setRenderMode(RenderMode mode)					{ if(!isInitialized) {tileMode = mode;}}	
	void setLoaded()									{ if(!isInitialized) {isMapLoaded = true;}}	
	//chunk rendering
	void setAtlasTexture(std::string location, sf::Texture* atlas)	{ if(!isInitialized) {textureAtlasLocation = location, textureAtlas = atlas;}}
	void setChunks_x(unsigned int x)								{ if(!isInitialized) {chunks_x = x;}}
	void setChunks_y(unsigned int y)								{ if(!isInitialized) {chunks_y = y;}}
	void setBorderMap(const std::string& name, utl::Direction dir);
	void setBorderMapOffset(int tileOffset, utl::Direction dir);

	std::string const& getName()		{return tileMapName;}
	int getID()	const					{return id;}
	std::vector <int>& getTileMap() 	{return tileMap;}
	std::map <int, Tile>& getTileKey() 	{return tileKey;}
	unsigned int getWidth() 			{return width;}
	unsigned int getHeight() 			{return height;}
	unsigned int getLayers() 			{return layers;}
	unsigned int getMaxTileSize_x() 	{return maxTileSize_x;}
	unsigned int getMaxTileSize_y() 	{return maxTileSize_y;}
	TextureMode  getTextureMode() 		{return textureMode;}
	RenderMode   getRenderMode() 		{return tileMode;}
	std::string  getAtlasLocation() 	{return textureAtlasLocation;}
	sf::Texture* getAtlas() 			{return textureAtlas;}
	bool isLoaded()						{return isMapLoaded;}
	//chunk rendering
	unsigned int getChunks_x()					{return chunks_x;}
	unsigned int getChunks_y()					{return chunks_y;}
	std::vector <sf::VertexArray>& getChunks()	{return chunkVector;}
	const std::string& getBorderMap(utl::Direction dir);
	int getBorderMapOffset(utl::Direction dir);

private:
	std::string tileMapName = std::string();
	int id = -1;
	//dimensions
	unsigned int width = 0, height = 0, layers = 0;
	//biggest sized tile dimensions
	unsigned int maxTileSize_x = 0, maxTileSize_y = 0;
	
	std::string borderMaps[4];
	int borderMapOffsets[4] = {0,0,0,0};

	//used if batching
	std::string textureAtlasLocation = std::string();
	sf::Texture* textureAtlas =  nullptr;

	//(width * height * layers) sized vector, holds tile ID
	std::vector <int> tileMap;
	//pass tileID, get Tile
	std::map <int, Tile> tileKey;
	
	///batch mode only
	//chunk size is 8x8 tiles
	std::vector <sf::VertexArray> chunkVector;
	//chunks
	unsigned int chunks_x = 0, chunks_y = 0;

	//once map set, not modifyable
	bool isInitialized = false;
	bool isMapLoaded = false;
};

#endif // TILEMAP_H
