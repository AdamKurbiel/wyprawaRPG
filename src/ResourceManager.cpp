#include "ResourceManager.hpp"
#include <iostream>

sf::Texture& ResourceManager::loadTexture(const std::string& name)
{
    auto it = textures.find(name);

    if (it != textures.end()) return it->second;

    sf::Texture texture;
    if (!texture.loadFromFile(name)) throw std::runtime_error("Couldn't load texture: " + name);

    textures[name] = std::move(texture);
    return textures[name];
}