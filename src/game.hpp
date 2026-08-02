#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "game.hpp"
#include "Systems/ResourceManager.hpp"
#include "UI/UiKeyboard.hpp"

class Game
{
    private:
        void inputCheck(UiKeyboard& virtualKeyboard, sf::RenderWindow& window);

    public:
        void run();
};