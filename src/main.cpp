#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cmath>
#include "Utils.hpp"

const float TILE_SIZE = 48.f;

class UiKeyboard {
	public:
		const std::string LETTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		const int COLUMNS = 3;
		std::string content = "";

		float cursor_x;
		float cursor_y;

		std::string currentlyHovering = "";
		
		float cursor_rx = cursor_x; //r means render (to lerp)
		float cursor_ry = cursor_y;

		void checkCursor(){
			int index = static_cast<int>((cursor_y - 1) * COLUMNS + (cursor_x - 1));

			if (index >= 0 && index < LETTERS.size())
			{
    			currentlyHovering = LETTERS[index];
			}
			else
			{
    			currentlyHovering = "OK";
			}
		}

		void checkKeyboardInput(sf::Keyboard::Key keyCode){
			if (keyCode == sf::Keyboard::Key::Left) cursor_x -= 1; 
			if (keyCode == sf::Keyboard::Key::Right) cursor_x += 1; 
			if (keyCode == sf::Keyboard::Key::Up) cursor_y -= 1; 
			if (keyCode == sf::Keyboard::Key::Down) cursor_y += 1;
			if (keyCode == sf::Keyboard::Key::Enter || keyCode == sf::Keyboard::Key::Space){
				if (currentlyHovering == "OK"){cursor_x = 1; cursor_y = 1; checkCursor(); return;}
				if (content.length() >= 10){return;}
				content += currentlyHovering;
			}
			if (keyCode == sf::Keyboard::Key::Backspace){
				content = content.substr(0,content.length()-1);
			}

			if (cursor_x > 3) cursor_x = 1;
			if (cursor_x < 1) cursor_x = 3;
			if (cursor_y > 9) cursor_y = 1;
			if (cursor_y < 1) cursor_y = 9;

			checkCursor();
		}

		void resetCursorPosition(){
			cursor_x = 1;
			cursor_y = 1;
			cursor_rx = 1;
			cursor_ry = 1;
		};

		void render(sf::RenderWindow &window, sf::Font font){
			

			float column = 1;
			float row = 1;
			for (int i = 1; i <= LETTERS.length(); i++){
				char key = LETTERS[i-1];
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
	sf::Clock clock;
	sf::Font GENERAL_FONT;
	if (!GENERAL_FONT.openFromFile("../assets/fonts/CastoroTitling.ttf"))
	{
		std::cout << "Couldn't find font: arial.ttf";
		return 0;
	}
	
	/*
	sf::Texture charactertexture;
	if (!charactertexture.loadFromFile("../assets/textures/cieniowanie.png")){
		return 0;
	}
	*/

	sf::Texture bg_blur;
	if (!bg_blur.loadFromFile("../assets/textures/bg_blur.png")){
		return 0;
	}


	sf::Texture char_warrior;
	if (!char_warrior.loadFromFile("../assets/textures/char_warrior.png")){
		return 0;
	}

	sf::Texture char_mage;
	if (!char_mage.loadFromFile("../assets/textures/char_mage.png")){
		return 0;
	}

	const int MAP_SIZE = 12;

	UiKeyboard virtualKeyboard;
	virtualKeyboard.resetCursorPosition();
	virtualKeyboard.checkCursor();

	sf::Text inputContent(GENERAL_FONT);
	inputContent.setPosition({TILE_SIZE*8.5,TILE_SIZE*2});
	
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
	keyboardCursor.setOutlineThickness(3.f);


	sf::Sprite bgblur(bg_blur);
	bgblur.setScale({4.5f,4.5f});
	bgblur.setPosition({-20.f,100.f});

	mainWindow.draw(bgblur);


	virtualKeyboard.render(mainWindow, GENERAL_FONT);

	virtualKeyboard.cursor_rx = lerp(virtualKeyboard.cursor_rx,virtualKeyboard.cursor_x,0.5f);
	virtualKeyboard.cursor_ry = lerp(virtualKeyboard.cursor_ry,virtualKeyboard.cursor_y,0.5f);
	keyboardCursor.setPosition({virtualKeyboard.cursor_rx * TILE_SIZE ,virtualKeyboard.cursor_ry * TILE_SIZE});
	mainWindow.draw(keyboardCursor);

	sf::Text infoText(GENERAL_FONT, "Insert Your character name.");
	infoText.setCharacterSize(24);
	infoText.setPosition({120.f,0.f});
	mainWindow.draw(infoText);

	inputContent.setString(virtualKeyboard.content);
	inputContent.setCharacterSize(40);
	sf::FloatRect bounds = inputContent.getLocalBounds();
	inputContent.setOrigin({
		bounds.position.x + bounds.size.x / 2,
		bounds.position.y + bounds.size.y / 2
	});
	
	float baseY = 160.f;
	float amplitude = 5.f;
	float speed = 2.f;
	inputContent.setPosition({
		inputContent.getPosition().x,
		baseY + std::sin(time * speed) * amplitude
	});
	mainWindow.draw(inputContent);

	baseY = 175.f;
	amplitude = 2.f;
	speed = 1.5f;	
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