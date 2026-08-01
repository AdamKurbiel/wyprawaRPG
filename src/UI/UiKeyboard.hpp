#pragma once

#include <string>
#include <SFML/Graphics.hpp>

class UiKeyboard {
private:
    const std::string LETTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const int COLUMNS = 3;

    float TILE_SIZE;

public:
    std::string content = "";

    float cursor_x;
    float cursor_y;

    std::string currentlyHovering = "";
    std::string input_question = "";

    float cursor_rx;
    float cursor_ry;

    UiKeyboard(std::string question, float tileSize);

    void checkCursor();
    void checkKeyboardInput(sf::Keyboard::Key keyCode);
    void resetCursorPosition();

    void render(sf::RenderWindow& window, const sf::Font& font, float time, float dt);
};