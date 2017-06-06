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
    ~ResourceManager() = default;
    sf::Texture& getTexture(const std::string& filename);
    sf::Texture& getBlankTexture(const std::string& textureName);
    bool isTexture(const std::string& textureName);
    void kill(const std::string& filename);

private:
    std::map <std::string, sf::Texture> textureMap {};
};

#endif // RESOURCEMANAGER_H
