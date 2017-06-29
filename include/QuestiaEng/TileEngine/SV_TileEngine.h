#ifndef SV_TILEENGINE_H
#define SV_TILEENGINE_H

#include <vector>

#include "SFML/Window.hpp"

#include "QuestiaEng/TileEngine/TileMap.h"

#include "QuestiaEng/Utl/Utl.h"
#include "QuestiaEng/Utl/Type/Vector2.h"
#include "QuestiaEng/Utl/Type/Vector2.h"
#include "QuestiaEng/Utl/SaveFile.h"
#include "QuestiaEng/Utl/FileData.h"

#include "QuestiaEng/TileEngine/Tile.h"

#include "QuestiaEng/Utl/TextureAtlas.h"

class SV_TileEngine
{
public:
	//ctor + dtor
	SV_TileEngine(ResourceManager& resourceManager);
	~SV_TileEngine();

	///game
	//loads the TileMap with tileKey and tileMap, loads texture either into Tile's in tileMap or ResourceManager texture TILESTORAGE_ + mapName
	TileMap openMap(const std::string& mapName, sf::RenderWindow& window, TileMap::TextureMode textureMode, TileMap::RenderMode tileMode);

	///editor
	//creating map
	bool createMap(const std::string& mapName, unsigned int width, unsigned int height, unsigned int layers);
	TileMap editMap(const std::string& mapName, sf::RenderWindow& window);
	//TODO implement this
	void changeMapDimensions(const std::string& mapName, unsigned int width, unsigned int height, unsigned int layers);
	//saving map and tiles used
	void saveMap(TileMap* map);

private:
	std::vector <std::pair <int, std::string> > getTileLocations(const std::string& fileDir, TileMap::TextureMode textureMode);
	//loads TileMap with tileKey, and if RenderMode = Batch, loads tileAtlas texture into TILESTORAGE_ + mapName in resourceManager
	//does not assume that every png file is accounted for that is referenced by txt files
	void loadTiles(std::vector <std::pair <int, std::string> >& tileLocations, TileMap& mapData, sf::RenderWindow& window, const std::string& mapName);
	//loads chunks if in batch mode, validates all sprites in sprite mode
	void loadRenderData(TileMap& mapData);

	//for getting coordinates
	int getTile(unsigned int x, unsigned int y, unsigned int layer, TileMap& tileMap);
	int getChunk(unsigned int x, unsigned int y, unsigned int layer, TileMap& tileMap);

	///names of items
	//mapInfo
	const std::string name_width = "width";
	const std::string name_height = "height";
	const std::string name_layers = "layers";
	const std::string name_map_up	 	 = "map_up";
	const std::string name_map_up_off 	 = "map_up_offset";
	const std::string name_map_down 	 = "map_down";
	const std::string name_map_down_off  = "map_down_offset";
	const std::string name_map_left 	 = "map_left";
	const std::string name_map_left_off  = "map_left_offset";
	const std::string name_map_right 	 = "map_right";
	const std::string name_map_right_off = "map_right_offset";

	//for tilework
	ResourceManager& resourceManager;

	TextureAtlas textureAtlas;

	const std::string file_mapInfo =   "/mapInfo.txt";
	const std::string file_tilesUsed = "/tilesUsed.txt";
	const std::string file_map =       "/map.txt";
};

#endif // SV_TILEENGINE_H
