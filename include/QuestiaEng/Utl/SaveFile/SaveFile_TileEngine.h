#ifndef SAVEFILE_TILEENGINE_H
#define SAVEFILE_TILEENGINE_H

#include <SFML/Window.hpp>
#include <vector>

#include "QuestiaEng/Utl/Utl.h"
#include "QuestiaEng/Utl/Type/Vector2.h"
#include "QuestiaEng/Utl/Type/Vector2.h"
#include "QuestiaEng/Utl/SaveFile/SaveFile.h"
#include "QuestiaEng/Utl/FileData.h"

#include "QuestiaEng/TileEngine/Tile.h"

#include "QuestiaEng/Utl/TextureAtlas.h"

///enums
namespace TileEng
{
enum class TextureMode  {Map, All};
enum class TileMode     {Sprite, Batch};
}


struct MapData
{
	//map
	std::vector <int> tileMap;
	//dimensions
	unsigned int width = 0, height = 0, layers = 0;
	//tile data
	std::map <int, Tile> tileStorage;
	//tile info
	unsigned int maxTileSize_x = 1, maxTileSize_y = 1;
};

struct TileTransform
{
	TileTransform(std::string _texturePath):texturePath(_texturePath) {}
	std::string texturePath;
	//(-1, -1) means sprite size
	utl::Vector2i tileSize = utl::Vector2i(-1, -1);
	//only 0, 90, 180, 270 are valid
	int degrees = 0;
	//only x, y, b(both), and n are valid
	char flip = 'n';
};

class SaveFile_TileEngine
{
public:
	//ctor + dtor
	SaveFile_TileEngine(ResourceManager& _resourceManager);
	~SaveFile_TileEngine();

	///game
	MapData openMap(std::string mapName, sf::RenderWindow& window, TileEng::TextureMode textureMode, TileEng::TileMode tileMode);

	///editor
	//creating map
	bool createMap(std::string mapName, unsigned int width, unsigned int height, unsigned int layers);
	MapData editMap(std::string mapName, sf::RenderWindow& window);
	void changeMapDimensions(std::string mapName, unsigned int width, unsigned int height, unsigned int layers);
	//saving map and tiles used
	void saveMap(std::string mapName, const std::vector <int>& tileMap, unsigned int width, unsigned int height, unsigned int layers, const std::map<int, Tile>& tilePairs);

	//helper
	int getTile(unsigned int x, unsigned int y, unsigned int layer, unsigned int mapWidth, unsigned int mapHeight);
private:
	std::vector <std::pair <int, std::string> > getTileLocations(std::string filePath, TileEng::TextureMode textureMode);
	void loadTiles(std::vector <std::pair <int, std::string> >& tileLocations, MapData& mapData, TileEng::TileMode tileMode, sf::RenderWindow& window);

	///names of items
	//mapInfo
	const std::string name_width = "width";
	const std::string name_height = "height";
	const std::string name_layers = "layers";

	//for tilework
	ResourceManager& resourceManager;

	//saves textures in 1 sheet
	TextureAtlas textureAtlas;

	const std::string file_mapInfo =   "/mapInfo.txt";
	const std::string file_tilesUsed = "/tilesUsed.txt";
	const std::string file_map =       "/map.txt";
};

#endif // SAVEFILE_TILEENGINE_H
