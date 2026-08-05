#include "GameMap.hpp"
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <unordered_map>

GameMap::GameMap(float tile_size){
    TILESIZE = tile_size;   
}

void GameMap::renderTile(sf::RenderWindow& window, int x, int y, int txt_id){
    /*TODO replace tile colors with actual textures
    (currently using tile colors as placeholders).*/
    sf::RectangleShape tile({TILESIZE,TILESIZE});
    tile.setFillColor(colormap[txt_id]);
    tile.setPosition({
        TILESIZE * x,
        TILESIZE * y
    });
    window.draw(tile);
}

void GameMap::render(sf::RenderWindow& window){
    int i = 0;

    int x = 0;
    int y = 0;

    while (i < content.size()){
        renderTile(window,x,y,content[i]);
        if ((i+1) % MAP_WIDTH == 0){
            y++;
            x = 0;
        }else x++;
        
        i++;
    }
}
void GameMap::printContent(){
    int i = 0;
    while (i < content.size())
    {
        std::cout << content.at(i);
        if ((i+1) % MAP_WIDTH == 0){
            std::cout << std::endl;
        }
        i++;
    }
    std::cout << std::endl;
}