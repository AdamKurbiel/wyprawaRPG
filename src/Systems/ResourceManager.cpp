/*
<Copyright Adam Kurbiel 2026>

Resource manager. Loads (In the future not only) textures when given path, and adds it to a map.
Reuses existing textures if map contains requested texture.

*/
#include "ResourceManager.hpp"
#include <iostream>

void ResourceManager::logResource(std::string name){
    //if (existing) std::cout << "[RM] Reloaded " << name << std::endl; return;
    std::cout << "[RM] Loaded " << name << std::endl;
}


sf::Texture& ResourceManager::loadTexture(const std::string& name)
{
    bool existing = false;
    auto it = textures.find(name);

    if (it != textures.end()){
        return it->second;
    }

    sf::Texture texture;
    if (!texture.loadFromFile(name)) throw std::runtime_error("Couldn't load texture: " + name);

    textures[name] = std::move(texture);
    
    logResource(name);
    return textures[name];
}

sf::Font& ResourceManager::loadFont(const std::string& name)
{
    auto it = fonts.find(name);
    if (it != fonts.end()){
        return it->second;
    } 

    sf::Font font;
    if (!font.openFromFile(name)) throw std::runtime_error("Couldn't load font: " + name);

    fonts[name] = std::move(font);

    logResource(name);
    return fonts[name];
}