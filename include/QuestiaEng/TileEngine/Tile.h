#ifndef TILE_H
#define TILE_H

#include <SFML/Window.hpp>

#include "QuestiaEng/Utl/Type/Rect.h"
#include "QuestiaEng/Utl/Type/Vector2.h"
#include "QuestiaEng/ResourceManager/ResourceManager.h"

#include "QuestiaEng/Utl/Utl.h"

#include <iostream>

class Tile
{
public:
	//ctor + dtor
	Tile(sf::RenderWindow& window, ResourceManager& resourceManager);
	~Tile() = default;

	//saves filePath and directory, and sets as display and texture path
	void setTexture(const std::string& filePath);
	//used to save tile after loading it
	void setSource(const std::string& filePath);
	//just sets the display name for the tile
	void setDisplay(const std::string& filePath);
	//texture size in tiles
	void setSize(unsigned int tilesWidth, unsigned int tilesHeight);
	void setSize_x(unsigned int tilesWidth);
	void setSize_y(unsigned int tilesHeight);
	//TODO make Rotate and Flip affect collision rect
	//only 0, 90, 180, 270 are valid rotations
	void setRotation(int degrees);
	//only x, y, b(both), and n are valid flips
	void setFlip(char direction);
	
	const std::string& getTexturePath() const;
	const std::string& getSource() const;
	const std::string& getDisplay() const;
	const std::string& getFolder() const;
	const std::string& getTileName() const;
	
	utl::Vector2i getSize() const;
	int getSize_x() const;
	int getSize_y() const;
	int getRotate() const;
	char getFlip() const;

	void setCollisionRect(int x, int y, int width, int height);
	utl::IntRect& getCollisionRect();

	//applies all transformations into sprite
	//does not need to be called for batch drawing
	void loadSprite();
	void setPosition(int x, int y);
	//only affects sprite rendering using drawTile()
	void setTransparency(int alpha);
	void drawTile();

	//only used for batch rendering
	utl::IntRect texturePosition = utl::IntRect(0,0,0,0);

	//general helpers
	bool isInTile(int x, int y);

private:
	sf::RenderWindow& window;
	ResourceManager& resourceManager;

	utl::Vector2i tileSize = utl::Vector2i(1, 1);
	int degrees = 0;
	char flip = 'n';

	//for editor
	std::string display = "Missing Texture";
	std::string texture = "Media/Image/Game/Tiles/Debug/Missing.png";
	std::string source = "Media/Image/Game/Tiles/Debug/Missing.png";
	std::string folder;
	std::string tileName;
	utl::Vector2i tilePosition;

	//only used for drawing as sprite
	sf::Sprite tileSprite;
	sf::Transform tileTransform;
	sf::Transform moveTransform;

	utl::IntRect collisionRect = utl::IntRect(0,0,-1,-1);
};


#endif // TILE_H
