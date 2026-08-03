#include <iostream>
#include <string>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "game.hpp"
#include "Systems/ResourceManager.hpp"

void Game::run(){
    const float TILE_SIZE = 48.f;
    ResourceManager rm;
	sf::Clock clock;
	sf::Clock frameClock;
	
	sf::Font GENERAL_FONT = rm.loadFont("../assets/fonts/CastoroTitling.ttf");
    
	sf::Texture bg_blur = rm.loadTexture("../assets/textures/bg_blur.png");
	sf::Texture char_warrior = rm.loadTexture("../assets/textures/char_warrior.png");
	sf::Texture char_mage = rm.loadTexture("../assets/textures/char_mage.png");

	sf::RenderWindow mainWindow( sf::VideoMode( { 640, 512 } ), "wyprawaRPG", sf::Style::Titlebar | sf::Style::Close);

	while (mainWindow.isOpen()){
		while (const auto event = mainWindow.pollEvent()){
			if (event->is<sf::Event::Closed>()){
				mainWindow.close();
				break;
			}
		}

		mainWindow.clear();	
	    sf::Sprite bgblur(bg_blur);
	    bgblur.setScale({4.5f,4.5f});
	    bgblur.setPosition({-20.f,100.f});
	    mainWindow.draw(bgblur);
		

		float time = clock.getElapsedTime().asSeconds();
		float dt = frameClock.restart().asSeconds();

	    float baseY = 175.f;
	    float amplitude = 2.f;
	    float speed = 1.5f;	
	    sf::Sprite warrior(char_warrior);
	    warrior.setScale({1.5f,1.5f});
	    warrior.setPosition({200.f,baseY + std::sin(time * speed) * amplitude});
	    mainWindow.draw(warrior);

	    sf::Sprite mage(char_mage);
	    mage.setScale({1.5f,1.5f});
	    mage.setPosition({390.f,baseY + std::sin(time * speed) * amplitude});
	    mainWindow.draw(mage);

	    mainWindow.display();
	}
}