/*
<Copyright Adam Kurbiel 2026>

Main file. Currently alot of things are stuck here and I need to find a way to move them in some single files.
The best approach is to make SceneManager.

*/
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cmath>
#include "Utils.hpp"
#include "ResourceManager.hpp"

const float TILE_SIZE = 48.f;

class UiKeyboard {
	//todo// more readability
	public:
		const std::string LETTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		const int COLUMNS = 3;
		std::string content = "";

		float cursor_x;
		float cursor_y;

		std::string currentlyHovering = "";
		std::string input_question = "";
		
		float cursor_rx = cursor_x; //r means render (to lerp)
		float cursor_ry = cursor_y;

		UiKeyboard(std::string question){
			input_question = question;
			resetCursorPosition();
			checkCursor();
		}

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

		void render(sf::RenderWindow& window, const sf::Font& font, float time)
		{
			cursor_rx = lerp(cursor_rx, cursor_x, 0.5f);
			cursor_ry = lerp(cursor_ry, cursor_y, 0.5f);
	
			sf::RectangleShape keyboardCursor({TILE_SIZE, TILE_SIZE});
			keyboardCursor.setFillColor(sf::Color::Transparent);
			keyboardCursor.setOutlineColor(sf::Color::Blue);
			keyboardCursor.setOutlineThickness(3.f);
			keyboardCursor.setPosition({
			    cursor_rx * TILE_SIZE,
			    cursor_ry * TILE_SIZE
			});
			
			float column = 1;
			float row = 1;
			for (int i = 0; i < LETTERS.size(); i++)
			{
			    sf::Text letter(font);
			    letter.setString(std::string(1, LETTERS[i]));
			    letter.setFillColor(sf::Color::White);
				
			    sf::FloatRect letterBounds = letter.getLocalBounds();
			    letter.setOrigin({
			        letterBounds.position.x + letterBounds.size.x / 2.f,
			        letterBounds.position.y + letterBounds.size.y / 2.f
			    });
				
			    letter.setPosition({
			        TILE_SIZE * row + TILE_SIZE / 2.f,
			        TILE_SIZE * column + TILE_SIZE / 2.f
			    });	
			    letter.setScale({0.9f, 1.f});
			    window.draw(letter);
				
			    row++;
			    if ((i + 1) % COLUMNS == 0)
			    {
			        row = 1;
			        column++;
			    }
			}
			
			sf::Text ok(font);
			ok.setString("OK");
			ok.setFillColor(sf::Color::White);
			sf::FloatRect okBounds = ok.getLocalBounds();
			ok.setOrigin({
			    okBounds.position.x + okBounds.size.x / 2.f,
			    okBounds.position.y + okBounds.size.y / 2.f
			});
			ok.setPosition({
			    TILE_SIZE * row + TILE_SIZE / 2.f,
			    TILE_SIZE * column + TILE_SIZE / 2.f
			});
			ok.setScale({0.8f, 1.f});
			window.draw(ok);
			
			sf::Text infoText(font);
			infoText.setString(input_question);
			infoText.setCharacterSize(24);
			sf::FloatRect infoBounds = infoText.getLocalBounds();
			infoText.setOrigin({
				infoBounds.position.x + infoBounds.size.x / 2.f,
				infoBounds.position.y + infoBounds.size.y / 2.f
			});
			infoText.setPosition({320.f, 20.f});
			window.draw(infoText);

			float baseY = 160.f;
			float amplitude = 5.f;
			float speed = 2.f;
			
			sf::Text inputContent(font);
			inputContent.setString(content);
			inputContent.setCharacterSize(40);
			sf::FloatRect inputBounds = inputContent.getLocalBounds();
			inputContent.setOrigin({
			    inputBounds.position.x + inputBounds.size.x / 2.f,
			    inputBounds.position.y + inputBounds.size.y / 2.f
			});
			inputContent.setPosition({
			    TILE_SIZE * 8.5f,
			    baseY + std::sin(time * speed) * amplitude
			});
			
			window.draw(keyboardCursor);
			window.draw(inputContent);
		}
};


int main()
{
	ResourceManager rm;
	sf::Clock clock;

	sf::Font GENERAL_FONT;
	if (!GENERAL_FONT.openFromFile("../assets/fonts/CastoroTitling.ttf")) return 0;
	
	sf::Texture bg_blur = rm.loadTexture("../assets/textures/bg_blur.png");
	sf::Texture char_warrior = rm.loadTexture("../assets/textures/char_warrior.png");
	sf::Texture char_mage = rm.loadTexture("../assets/textures/char_mage.png");
	UiKeyboard virtualKeyboard("Insert character's name.");

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