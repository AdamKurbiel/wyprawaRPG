/*
<Copyright Adam Kurbiel 2026>

Main file. Currently alot of things are stuck here and I need to find a way to move them in some single files.
The best approach is to make SceneManager.

*/
#include <iostream>
#include <string>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "Systems/ResourceManager.hpp"
#include "UI/UiKeyboard.hpp"

const float TILE_SIZE = 48.f;

int main()
{
	ResourceManager rm;
	sf::Clock clock;

	sf::Font GENERAL_FONT;
	if (!GENERAL_FONT.openFromFile("../assets/fonts/CastoroTitling.ttf")) return 0;
	
	sf::Texture bg_blur = rm.loadTexture("../assets/textures/bg_blur.png");
	sf::Texture char_warrior = rm.loadTexture("../assets/textures/char_warrior.png");
	sf::Texture char_mage = rm.loadTexture("../assets/textures/char_mage.png");
	UiKeyboard virtualKeyboard("Insert character's name.",TILE_SIZE);

	sf::RenderWindow mainWindow( sf::VideoMode( { 640, 512 } ), "wyprawaRPG", sf::Style::Titlebar | sf::Style::Close);

	while ( mainWindow.isOpen() )
	{
		float time = clock.getElapsedTime().asSeconds();

		while (const auto event = mainWindow.pollEvent())
		{
    		if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
    		{
				sf::Keyboard::Key KeyCode = keyPressed->code; //KEY

				virtualKeyboard.checkKeyboardInput(KeyCode);

        		if (keyPressed->code == sf::Keyboard::Key::Escape) mainWindow.close();
    		}

			if ( event->is<sf::Event::Closed>() ) mainWindow.close();
		}

		mainWindow.clear();
	
	sf::Sprite bgblur(bg_blur);
	bgblur.setScale({4.5f,4.5f});
	bgblur.setPosition({-20.f,100.f});

	mainWindow.draw(bgblur);
	virtualKeyboard.render(mainWindow, GENERAL_FONT, time);

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
};