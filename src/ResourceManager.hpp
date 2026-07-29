#pragma once

#include <unordered_map>
#include <string>
#include <SFML/Graphics.hpp>

class ResourceManager {
    private:
        std::unordered_map<std::string, sf::Texture> textures;

    public:
        sf::Texture& loadTexture(const std::string& name);
};