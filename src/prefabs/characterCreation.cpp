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
	
		sf::Text tooltip(GENERAL_FONT,"arrows - movement | space/enter - select");
		tooltip.setCharacterSize(16);
    	auto tooltip_bounds = tooltip.getLocalBounds();
    	tooltip.setOrigin({
        	tooltip_bounds.position.x + tooltip_bounds.size.x / 2.f,
        	tooltip_bounds.position.y + tooltip_bounds.size.y / 1.f
    	});
    	tooltip.setPosition({
        	window.getSize().x / 2.f,
			window.getSize().y /1.f - 5.f
 	   });
	   window.draw(tooltip);

		window.display();
	}

	char_name = vk.content;
}
void Character::set_class(ResourceManager& rm, sf::RenderWindow& window){
    const float TILE_SIZE = 48.f;

	sf::Clock clock;
	sf::Clock frameClock;
	
	sf::Font GENERAL_FONT = rm.loadFont("../assets/fonts/CastoroTitling.ttf");
	sf::Text character_name(GENERAL_FONT,char_name);	

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

		character_name.setCharacterSize(48);
    	auto character_name_bounds = character_name.getLocalBounds();
    	character_name.setOrigin({
        	character_name_bounds.position.x + character_name_bounds.size.x / 2.f,
        	character_name_bounds.position.y + character_name_bounds.size.y / 2.f
    	});
    	character_name.setPosition({
        	window.getSize().x / 2.f,
			30.f
		});
		window.draw(character_name);

		sf::Text objective(GENERAL_FONT,"Select your character class.");
		objective.setCharacterSize(24);
    	auto objective_bounds = objective.getLocalBounds();
    	objective.setOrigin({
        	objective_bounds.position.x + objective_bounds.size.x / 2.f,
        	objective_bounds.position.y + objective_bounds.size.y / 2.f
    	});
    	objective.setPosition({
        	window.getSize().x / 2.f,
			70.f
 	   });
	   window.draw(objective);

		sf::Text tooltip(GENERAL_FONT,"arrows - movement | space/enter - select");
		tooltip.setCharacterSize(16);
    	auto tooltip_bounds = tooltip.getLocalBounds();
    	tooltip.setOrigin({
        	tooltip_bounds.position.x + tooltip_bounds.size.x / 2.f,
        	tooltip_bounds.position.y + tooltip_bounds.size.y / 1.f
    	});
    	tooltip.setPosition({
        	window.getSize().x / 2.f,
			window.getSize().y /1.f - 5.f
		});
		window.draw(tooltip);
	   
		window.display();
	}

	char_class = "";
}