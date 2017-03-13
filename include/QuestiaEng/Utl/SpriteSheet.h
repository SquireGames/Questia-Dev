#ifndef STRUCT_ANIMATION_H
#define STRUCT_ANIMATION_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <map>
#include "QuestiaEng/ResourceManager/ResourceManager.h"

#include <iostream>

class SpriteSheet
{
public:
    SpriteSheet(ResourceManager& _resourceManager, std::string imageLocation, unsigned int slides_x, unsigned int slides_y);
    SpriteSheet(ResourceManager& _resourceManager);

    void loadSprite(std::string imageLocation, unsigned int slides_x, unsigned int slides_y);

    sf::Sprite& getSprite(unsigned int map_x, unsigned int map_y);

    unsigned int getSheetWidth();
    unsigned int getSheetHeight();

    void setSize(float width, float height);
    void setOrigin(float x, float y);

private:
    //default
    ResourceManager &res;

    //saves sprites
    std::map<int, std::map<int, sf::Sprite> > spriteMap;

    //size of individual sheet
    unsigned int size_x = 0, size_y = 0;
};

#endif // STRUCT_ANIMATION_H
