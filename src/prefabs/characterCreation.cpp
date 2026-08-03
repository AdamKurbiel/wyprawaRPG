#include <SFML/Graphics.hpp>
#include "characterCreation.hpp"
#include "../UI/UiKeyboard.hpp"
#include "../Systems/ResourceManager.hpp"

std::string CharacterCreation::run(ResourceManager rm, sf::RenderWindow& window){
    const float TILE_SIZE = 48.f;

	sf::Clock clock;
	sf::Clock frameClock;
	
	sf::Font GENERAL_FONT = rm.loadFont("../assets/fonts/CastoroTitling.ttf");
	sf::Texture bg_blur = rm.loadTexture("../assets/textures/bg_blur.png");
	sf::Texture char_warrior = rm.loadTexture("../assets/textures/char_warrior.png");
	sf::Texture char_mage = rm.loadTexture("../assets/textures/char_mage.png");

	UiKeyboard vk("Insert character's name.",TILE_SIZE);

	while (vk.enabled){
		while (const auto event = window.pollEvent()){
			if (event->is<sf::Event::Closed>()){
				window.close();
				break;
			}

			if (vk.enabled){
				vk.handleEvent(*event);
			}
		}
		window.clear();	
		
		float time = clock.getElapsedTime().asSeconds();
		float dt = frameClock.restart().asSeconds();
		if (vk.enabled) vk.render(window, GENERAL_FONT, time, dt);
	    window.display();
	}

    return vk.content;
}

std::string CharacterClass::run(ResourceManager rm, sf::RenderWindow& window){
    const float TILE_SIZE = 48.f;

	sf::Clock clock;
	sf::Clock frameClock;
	
	sf::Font GENERAL_FONT = rm.loadFont("../assets/fonts/CastoroTitling.ttf");
	sf::Texture bg_blur = rm.loadTexture("../assets/textures/bg_blur.png");
	sf::Texture char_warrior = rm.loadTexture("../assets/textures/char_warrior.png");
	sf::Texture char_mage = rm.loadTexture("../assets/textures/char_mage.png");

	UiKeyboard vk("Insert character's name.",TILE_SIZE);

	while (vk.enabled){
		while (const auto event = window.pollEvent()){
			if (event->is<sf::Event::Closed>()){
				window.close();
				break;
			}

			if (vk.enabled){
				vk.handleEvent(*event);
			}
		}
		window.clear();	
		
		float time = clock.getElapsedTime().asSeconds();
		float dt = frameClock.restart().asSeconds();
		if (vk.enabled) vk.render(window, GENERAL_FONT, time, dt);
	    window.display();
	}

    return vk.content;
}