#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "game.hpp"
#include "Systems/ResourceManager.hpp"

class Game
{
    public:
        const float TILE_SIZE = 48.f;
        void run(ResourceManager& rm, sf::RenderWindow&);
};