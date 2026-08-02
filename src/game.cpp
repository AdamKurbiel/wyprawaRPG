#include <iostream>
#include <string>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "game.hpp"
#include "Systems/ResourceManager.hpp"
#include "UI/UiKeyboard.hpp"

void Game::inputCheck(UiKeyboard& virtualKeyboard, sf::RenderWindow& window)
{
	while (const auto event = window.pollEvent())
	{
		if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
		{
			virtualKeyboard.checkKeyboardInput(keyPressed->code);

			sf::Keyboard::Scancode scancode = keyPressed->scancode;
			std::string keycode = sf::Keyboard::getDescription(scancode).toAnsiString();
			std::cout << keycode << '\n';
		}

		if (event->is<sf::Event::Closed>())
			window.close();
	}
}

void Game::run(){
    const float TILE_SIZE = 48.f;

    ResourceManager rm;
	sf::Clock clock;
	sf::Clock frameClock;
	

	sf::Font GENERAL_FONT = rm.loadFont("../assets/fonts/CastoroTitling.ttf");
	 
	sf::Texture bg_blur = rm.loadTexture("../assets/textures/bg_blur.png");
	sf::Texture char_warrior = rm.loadTexture("../assets/textures/char_warrior.png");
	sf::Texture char_mage = rm.loadTexture("../assets/textures/char_mage.png");

	UiKeyboard virtualKeyboard("Insert character's name.",TILE_SIZE);

	sf::RenderWindow mainWindow( sf::VideoMode( { 640, 512 } ), "wyprawaRPG", sf::Style::Titlebar | sf::Style::Close);

	while ( mainWindow.isOpen() )
	{
        inputCheck(virtualKeyboard, mainWindow);

		float time = clock.getElapsedTime().asSeconds();
		float dt = frameClock.restart().asSeconds();

		mainWindow.clear();	
	
	    sf::Sprite bgblur(bg_blur);
	    bgblur.setScale({4.5f,4.5f});
	    bgblur.setPosition({-20.f,100.f});

	    mainWindow.draw(bgblur);
	    virtualKeyboard.render(mainWindow, GENERAL_FONT, time, dt);

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