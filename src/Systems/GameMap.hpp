#pragma once

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <map>

class GameMap{
    private:
        std::map<int, sf::Color> colormap = {
            {0, sf::Color::Green},
            {1, sf::Color::Magenta}
        };
        void renderTile(sf::RenderWindow& window, int x, int y, int txt_id);
    public:
        float TILESIZE = 48.f;
        int MAP_WIDTH = 10;
        std::vector<int> content = {
            0,0,0,0,0,0,0,0,0,1,
            0,0,0,0,1,1,1,1,0,1,
            0,0,0,0,1,0,0,1,0,1,
            0,0,0,0,1,0,0,1,1,1,
            0,0,0,0,1,0,0,0,0,1,
            0,0,0,0,1,0,0,0,0,1,
            0,0,0,0,0,0,0,0,0,1,
            0,0,0,0,0,0,0,0,0,0
        };
        GameMap(float tile_size);

        void render(sf::RenderWindow& window);
        void printContent();
};