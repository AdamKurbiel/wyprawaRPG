/*
<Copyright Adam Kurbiel 2026>

UI element: Keyboard input.
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include "UiKeyboard.hpp"
#include <algorithm>
#include <cmath>
#include "../Utils/Utils.hpp"


UiKeyboard::UiKeyboard(std::string question, float tileSize){
    input_question = question;
    TILE_SIZE = tileSize;

    resetCursorPosition();
    checkCursor();
}

void UiKeyboard::checkCursor(){
    int index = static_cast<int>((cursor_y - 1) * COLUMNS + (cursor_x - 1));

    if (index >= 0 && index < LETTERS.size()){
        currentlyHovering = LETTERS[index];
    }else{
        currentlyHovering = "OK";
}}


void UiKeyboard::checkKeyboardInput(sf::Keyboard::Key keyCode){
    if (keyCode == sf::Keyboard::Key::Left) cursor_x -= 1;
    if (keyCode == sf::Keyboard::Key::Right) cursor_x += 1;
    if (keyCode == sf::Keyboard::Key::Up) cursor_y -= 1;
    if (keyCode == sf::Keyboard::Key::Down) cursor_y += 1;


    if (keyCode == sf::Keyboard::Key::Enter ||
        keyCode == sf::Keyboard::Key::Space){
        if (currentlyHovering == "OK"){
            cursor_x = 1;
            cursor_y = 1;
            checkCursor();
            enabled = false;
            return;
        }

        if (content.length() >= 10) return;

        content += currentlyHovering;
    }


    if (keyCode == sf::Keyboard::Key::Backspace)
    {
        if (!content.empty())
            content.pop_back();
    }


    if (cursor_x > 3) cursor_x = 1;
    if (cursor_x < 1) cursor_x = 3;

    if (cursor_y > 9) cursor_y = 1;
    if (cursor_y < 1) cursor_y = 9;


    checkCursor();
}

bool UiKeyboard::handleEvent(const sf::Event& event){
    if (!event.is<sf::Event::KeyPressed>())
        return false;

    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()){
        checkKeyboardInput(keyPressed->code);
        return true;
    }

    return false;
}

void UiKeyboard::resetCursorPosition(){
    cursor_x = 1;
    cursor_y = 1;

    cursor_rx = 1;
    cursor_ry = 1;
}


void UiKeyboard::render(sf::RenderWindow& window, const sf::Font& font, float time, float deltaTime){
    constexpr float speed = 25.f;
    const float alpha = std::clamp(speed * deltaTime, 0.f, 1.f);

    cursor_rx = utils::lerp(cursor_rx, cursor_x, alpha);
    cursor_ry = utils::lerp(cursor_ry, cursor_y, alpha);


    sf::RectangleShape keyboardCursor({TILE_SIZE, TILE_SIZE});

    keyboardCursor.setFillColor(sf::Color::Transparent);
    keyboardCursor.setOutlineColor(sf::Color::Blue);
    keyboardCursor.setOutlineThickness(3.f);

    keyboardCursor.setPosition({
        roundf(cursor_rx * TILE_SIZE),
        roundf(cursor_ry * TILE_SIZE)
    });


    float column = 1;
    float row = 1;


    for (int i = 0; i < LETTERS.size(); i++)
    {
        sf::Text letter(font);

        letter.setString(std::string(1, LETTERS[i]));
        letter.setFillColor(sf::Color::White);


        auto bounds = letter.getLocalBounds();

        letter.setOrigin({
            bounds.position.x + bounds.size.x / 2.f,
            bounds.position.y + bounds.size.y / 2.f
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

    auto okBounds = ok.getLocalBounds();

    ok.setOrigin({
        okBounds.position.x + okBounds.size.x / 2.f,
        okBounds.position.y + okBounds.size.y / 2.f
    });


    ok.setPosition({
        TILE_SIZE * row + TILE_SIZE / 2.f,
        TILE_SIZE * column + TILE_SIZE / 2.f
    });


    window.draw(ok);


    sf::Text infoText(font);
    infoText.setString(input_question);
    infoText.setCharacterSize(24);

    auto infoBounds = infoText.getLocalBounds();

    infoText.setOrigin({
        infoBounds.position.x + infoBounds.size.x / 2.f,
        infoBounds.position.y + infoBounds.size.y / 2.f
    });

    infoText.setPosition({320.f, 20.f});

    window.draw(infoText);

    sf::Text inputContent(font);

    inputContent.setString(content);
    inputContent.setCharacterSize(40);

    auto inputBounds = inputContent.getLocalBounds();

    inputContent.setOrigin({
        inputBounds.position.x + inputBounds.size.x / 2.f,
        inputBounds.position.y + inputBounds.size.y / 2.f
    });
    inputContent.setPosition({
        TILE_SIZE * 8.5f,
        160.f + std::sin(time * 2.f) * 5.f
    });


    window.draw(keyboardCursor);
    window.draw(inputContent);
}