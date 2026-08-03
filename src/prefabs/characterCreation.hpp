#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include "../Systems/ResourceManager.hpp"

class CharacterCreation{
    public:
        std::string run(ResourceManager rm, sf::RenderWindow& window);
};

class CharacterClass{
    public:
        std::string run(ResourceManager rm, sf::RenderWindow& window);
};