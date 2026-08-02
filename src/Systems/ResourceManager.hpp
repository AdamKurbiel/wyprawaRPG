#pragma once

#include <unordered_map>
#include <string>
#include <SFML/Graphics.hpp>

class ResourceManager {
    private:
        std::unordered_map<std::string, sf::Texture> textures;
        std::unordered_map<std::string, sf::Font> fonts;

        void logResource(std::string name);

    public:
        sf::Texture& loadTexture(const std::string& name);
        sf::Font& loadFont(const std::string& name);
};