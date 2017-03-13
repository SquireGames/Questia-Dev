#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <iostream>

class ResourceManager
{
public:
    ResourceManager();
    ~ResourceManager();
    sf::Texture& getTexture(std::string filename);
    sf::Texture& getBlankTexture(std::string textureName);
    bool isTexture(std::string textureName);
    void kill(std::string filename);

private:
    std::map <std::string, sf::Texture> textureMap {};
    bool firstTime = true;
};

#endif // RESOURCEMANAGER_H
