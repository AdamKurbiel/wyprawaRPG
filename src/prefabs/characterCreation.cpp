#include <SFML/Graphics.hpp>
#include "characterCreation.hpp"
#include "../UI/UiKeyboard.hpp"
#include "../Systems/ResourceManager.hpp"

void Character::set_name(ResourceManager& rm, sf::RenderWindow& window){
    const float TILE_SIZE = 48.f;

	sf::Clock clock;
	sf::Clock frameClock;
	
	sf::Font GENERAL_FONT = rm.loadFont("../assets/fonts/CastoroTitling.ttf");

	UiKeyboard vk("Insert character's name.",TILE_SIZE);

	while (vk.enabled && window.isOpen()){
		while (const auto event = window.pollEvent()){
			if (event->is<sf::Event::Closed>()){
			 	std::exit(0);
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

	char_name = vk.content;
}
void Character::set_class(ResourceManager& rm, sf::RenderWindow& window){
    const float TILE_SIZE = 48.f;

	sf::Clock clock;
	sf::Clock frameClock;
	
	sf::Font GENERAL_FONT = rm.loadFont("../assets/fonts/CastoroTitling.ttf");
	sf::Texture bg_blur = rm.loadTexture("../assets/textures/bg_blur.png");
	sf::Texture char_warrior = rm.loadTexture("../assets/textures/char_warrior.png");
	sf::Texture char_mage = rm.loadTexture("../assets/textures/char_mage.png");

	while (true && window.isOpen()){
		while (const auto event = window.pollEvent()){
			if (event->is<sf::Event::Closed>()){
				std::exit(0);
			}

			/*
			if (vk.enabled){
				vk.handleEvent(*event);
			}
			*/
		}
		window.clear();	
		

		sf::Text character_name(GENERAL_FONT,char_name);
		character_name.setCharacterSize(48);
    	auto Bounds = character_name.getLocalBounds();
    	character_name.setOrigin({
        	Bounds.position.x + Bounds.size.x / 2.f,
        	Bounds.position.y + Bounds.size.y / 2.f
    	});
    	character_name.setPosition({
        	window.getSize().x / 2.f,
			30.f
		});
		window.draw(character_name);
		
	 
		sf::Text objective(GENERAL_FONT,"Select your character class.");
		objective.setCharacterSize(24);
    	Bounds = objective.getLocalBounds();
    	objective.setOrigin({
        	Bounds.position.x + Bounds.size.x / 2.f,
        	Bounds.position.y + Bounds.size.y / 2.f
    	});
    	objective.setPosition({
        	window.getSize().x / 2.f,
			70.f
 	   });
	   window.draw(objective);
		
		float time = clock.getElapsedTime().asSeconds();
		float dt = frameClock.restart().asSeconds();
	    window.display();
	}

	char_class = "";
}