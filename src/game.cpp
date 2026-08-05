/*
<Copyright Adam Kurbiel 2026>

Main game script. It is responsible for handling maps, game events etc.

*/

#include <iostream>
#include <string>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "game.hpp"
#include "Systems/ResourceManager.hpp"
#include "Prefabs/characterCreation.hpp"

void Game::run(ResourceManager& rm, sf::RenderWindow& window, Character character{
    const float TILE_SIZE = 48.f;
	sf::Clock clock;
	sf::Clock frameClock;
	
	sf::Font GENERAL_FONT = rm.loadFont("../assets/fonts/CastoroTitling.ttf");

	while (window.isOpen()){
		while (const auto event = window.pollEvent()){
			if (event->is<sf::Event::Closed>())std::exit(0);
		}
		window.clear();

	    window.display();
	}
}