#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "Utils.hpp"

const float TILE_SIZE = 48.f;

class UiKeyboard {
	public:
		float cursor_x;
		float cursor_y;
		
		void checkKeyboardInput(sf::Keyboard::Key keyCode){
			if (keyCode == sf::Keyboard::Key::Left) cursor_x -= 1; 
			if (keyCode == sf::Keyboard::Key::Right) cursor_x += 1; 
			if (keyCode == sf::Keyboard::Key::Up) cursor_y -= 1; 
			if (keyCode == sf::Keyboard::Key::Down) cursor_y += 1;

			if (cursor_x > 3) cursor_x = 1;
			if (cursor_x < 1) cursor_x = 3;
			if (cursor_y > 9) cursor_y = 1;
			if (cursor_y < 1) cursor_y = 9;
		}

		void resetCursorPosition(){
			cursor_x = 1;
			cursor_y = 1;
		};

		void render(sf::RenderWindow &window, sf::Font font){
			std::string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
			
			const int COLUMNS = 3;

			float column = 1;
			float row = 1;
			for (int i = 1; i <= letters.length(); i++){
				char key = letters[i-1];
				sf::Text letter(font);
				letter.setString(key);
				letter.setFillColor(sf::Color::White);


				sf::FloatRect bounds = letter.getLocalBounds();
				letter.setOrigin({
					bounds.position.x + bounds.size.x / 2,
					bounds.position.y + bounds.size.y / 2
				});

				letter.setPosition({
					TILE_SIZE * row + TILE_SIZE / 2,
					TILE_SIZE * column + TILE_SIZE / 2
				});
				letter.setScale({0.9f,1.f});

				window.draw(letter);

				row++;
				if (i % COLUMNS == 0){
					row = 1;	
					column++;
				}
				
			}

			sf::Text letter(font, "OK");
			letter.setFillColor(sf::Color::White);
			sf::FloatRect bounds = letter.getLocalBounds();
			letter.setOrigin({
					bounds.position.x + bounds.size.x / 2,
					bounds.position.y + bounds.size.y / 2
			});

			letter.setPosition({
				TILE_SIZE * row + TILE_SIZE / 2,
				TILE_SIZE * column + TILE_SIZE / 2
			});
			letter.setScale({0.8f,1.f});
			window.draw(letter);
		}
};



int main()
{
	sf::Font GENERAL_FONT;
	if (!GENERAL_FONT.openFromFile("../assets/fonts/arial.ttf"))
	{
		std::cout << "Couldn't find font: arial.ttf";
		return 0;
	}

	const int MAP_SIZE = 12;

	UiKeyboard virtualKeyboard;
	virtualKeyboard.resetCursorPosition();


	sf::RenderWindow mainWindow( sf::VideoMode( { 640, 512 } ), "wyprawaRPG", sf::Style::Titlebar | sf::Style::Close);

	while ( mainWindow.isOpen() )
	{
		while (const auto event = mainWindow.pollEvent())
		{
    		if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
    		{
				sf::Keyboard::Key KeyCode = keyPressed->code; //KEY


				virtualKeyboard.checkKeyboardInput(KeyCode);


        		if (keyPressed->code == sf::Keyboard::Key::Escape)
        		{
            		mainWindow.close();
        		}
    		}

			if ( event->is<sf::Event::Closed>() ) mainWindow.close();
		}

		mainWindow.clear();
		

	/*
	for (int y = 0; y < MAP_SIZE; y++)
	{
    	for (int x = 0; x < MAP_SIZE; x++)
    	{
        	sf::RectangleShape tile({TILE_SIZE, TILE_SIZE});
        	tile.setFillColor(sf::Color::Green);
			if ((x + y) % 2) tile.setFillColor(sf::Color::Red);

        	tile.setPosition({
            	x * TILE_SIZE,
            	y * TILE_SIZE
        	});

        	window.draw(tile);
    	}
	}
	*/

	sf::RectangleShape keyboardCursor({TILE_SIZE, TILE_SIZE});
	keyboardCursor.setFillColor(sf::Color::Transparent);
	keyboardCursor.setOutlineColor(sf::Color::Blue);
	keyboardCursor.setOutlineThickness(2.f);

	keyboardCursor.setPosition({virtualKeyboard.cursor_x * TILE_SIZE ,virtualKeyboard.cursor_y * TILE_SIZE});
	mainWindow.draw(keyboardCursor);

	virtualKeyboard.render(mainWindow, GENERAL_FONT);

	sf::Text debugText(GENERAL_FONT);	
	debugText.setString("x:"+std::to_string(int(virtualKeyboard.cursor_x)) + "\ny:" + std::to_string(int(virtualKeyboard.cursor_y)));
	debugText.setCharacterSize(14);
	debugText.setFillColor(sf::Color::White);
	debugText.setStyle(sf::Text::Bold);
	mainWindow.draw(debugText);

	

	mainWindow.display();
	}
};