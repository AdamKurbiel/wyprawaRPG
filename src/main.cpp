#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

int main()
{
	sf::Font font;
	if (!font.openFromFile("../assets/fonts/arial.ttf"))
	{
		std::cout << "Couldn't find font: arial.ttf";
		return 0;
	}

	const float TILE_SIZE = 48.f;
	float TILE_PADDING = 0.f;
	int MAP_SIZE = 12;


	float plr_x = TILE_SIZE * 1;
	float plr_y = TILE_SIZE * 2;


	sf::RenderWindow window( sf::VideoMode( { 640, 512 } ), "wyprawaRPG" );

	while ( window.isOpen() )
	{
		while (const auto event = window.pollEvent())
		{
    		if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
    		{
        		if (keyPressed->code == sf::Keyboard::Key::Left)
        		{
					plr_x -= TILE_SIZE;
       			}
        		if (keyPressed->code == sf::Keyboard::Key::Right)
        		{
					plr_x += TILE_SIZE;
       			}
        		if (keyPressed->code == sf::Keyboard::Key::Up)
        		{
					plr_y -= TILE_SIZE;
       			}
        		if (keyPressed->code == sf::Keyboard::Key::Down)
        		{
					plr_y += TILE_SIZE;
       			}

        		if (keyPressed->code == sf::Keyboard::Key::Escape)
        		{
            		window.close();
        		}
    		}

			if ( event->is<sf::Event::Closed>() ) window.close();
		}

	window.clear();

	for (int y = 0; y < MAP_SIZE; y++)
	{
    	for (int x = 0; x < MAP_SIZE; x++)
    	{
        	sf::RectangleShape tile({TILE_SIZE, TILE_SIZE});
        	tile.setFillColor(sf::Color::Green);
			if ((x + y) % 2) tile.setFillColor(sf::Color::Red);

        	tile.setPosition({
            	x * TILE_SIZE + (TILE_SIZE * TILE_PADDING * x),
            	y * TILE_SIZE + (TILE_SIZE * TILE_PADDING * y)
        	});

        	window.draw(tile);
    	}
	}

	sf::RectangleShape player({TILE_SIZE, TILE_SIZE*2});
	player.setFillColor(sf::Color::Blue);
	player.setPosition({plr_x,plr_y});
	window.draw(player);

	sf::Text debugText(font);	
	debugText.setString("x:"+std::to_string(plr_x/TILE_SIZE) + "\ny:" + std::to_string(plr_y/TILE_SIZE));
	debugText.setCharacterSize(14);
	debugText.setFillColor(sf::Color::Black);
	debugText.setStyle(sf::Text::Bold);
	window.draw(debugText);

	sf::Text debugTextShadow(font);	
	debugTextShadow.setPosition({1,1});
	debugTextShadow.setString("x:"+std::to_string(plr_x/TILE_SIZE) + "\ny:" + std::to_string(plr_y/TILE_SIZE));
	debugTextShadow.setCharacterSize(14);
	debugTextShadow.setFillColor(sf::Color::White);
	debugTextShadow.setStyle(sf::Text::Bold);
	window.draw(debugTextShadow);

	window.display();
	}
};