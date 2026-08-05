#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include "../Systems/ResourceManager.hpp"

class Character{  
    public:
        std::string char_name = "";
        std::string char_class = "";
        int chosen_class_index = 0;

        void set_name(ResourceManager& rm, sf::RenderWindow& window);
        void set_class(ResourceManager& rm, sf::RenderWindow& window);
};