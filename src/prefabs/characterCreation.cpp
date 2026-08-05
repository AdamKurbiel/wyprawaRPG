#include <SFML/Graphics.hpp>
#include "characterCreation.hpp"
#include "../UI/UiKeyboard.hpp"
#include "../Systems/ResourceManager.hpp"
#include "classSelect.hpp"
#include "../Utils/Utils.hpp"

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
	ClassSelect cs;
	sf::Texture class_textures[4] = {
		rm.loadTexture("../assets/textures/knight.png"),
		rm.loadTexture("../assets/textures/knight.png"),
		rm.loadTexture("../assets/textures/knight.png"),
		rm.loadTexture("../assets/textures/knight.png")
	};

	std::array<float, 4> class_y = {55.f, 55.f, 55.f, 55.f};

	while (cs.enabled && window.isOpen()){
		float time = clock.getElapsedTime().asSeconds();
		float dt = frameClock.restart().asSeconds();
		while (const auto event = window.pollEvent()){
			if (event->is<sf::Event::Closed>()){
				std::exit(0);
			}

			
			if (cs.enabled){
				cs.handleEvent(*event);
			}
			
		}
		window.clear();

		for (int i = 0; i < 4; i++){
			float target_y = 55.f;
			if (cs.selected == i) target_y = 30.f;
			constexpr float speed = 10.f;
			const float alpha = std::clamp(speed * dt, 0.f, 1.f);
    		class_y[i] = utils::lerp(class_y[i], target_y, alpha);

			sf::Texture& txt = class_textures[i];
			sf::Sprite class_sprite(txt);
			class_sprite.setScale({0.20f,0.20f});
			class_sprite.setPosition({(156.f * i) - 64.f, class_y[i]});
			
			window.draw(class_sprite);
		}

		sf::Text objective(GENERAL_FONT,"Select your character class.");
		objective.setCharacterSize(24);
    	auto objective_bounds = objective.getLocalBounds();
    	objective.setOrigin({
        	objective_bounds.position.x + objective_bounds.size.x / 2.f,
        	objective_bounds.position.y + objective_bounds.size.y / 2.f
    	});
    	objective.setPosition({
        	window.getSize().x / 2.f,
			20.f
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
	
		if (cs.enabled) cs.render(window, GENERAL_FONT, time, dt);

		window.display();
	}

	char_class = "";
}