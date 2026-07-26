#include <SFML/Graphics.hpp>


int main()
{
	sf::RenderWindow window( sf::VideoMode( { 640, 512 } ), "wyprawaRPG" );

	while ( window.isOpen() )
	{
		while ( const std::optional event = window.pollEvent() )
		{
			if ( event->is<sf::Event::Closed>() )
				window.close();
		}

	window.clear();

	const float TILE_SIZE = 48.f;
	const float TILE_PADDING = 0.f;
	const int MAP_SIZE = 10;

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

		window.display();
	}
}