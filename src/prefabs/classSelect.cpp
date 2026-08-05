/*
<Copyright Adam Kurbiel 2026>

UI element: Keyboard input.
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include <cmath>
#include "../Utils/Utils.hpp"
#include "classSelect.hpp"

void ClassSelect::checkKeyboardInput(sf::Keyboard::Key keyCode){
    if (keyCode == sf::Keyboard::Key::Left) selected -= 1;
    if (keyCode == sf::Keyboard::Key::Right) selected += 1;

    if (keyCode == sf::Keyboard::Key::Enter ||
        keyCode == sf::Keyboard::Key::Space){
            content = classes[selected];
            enabled = false;
    }

    if (selected > 3) selected = 0;
    if (selected < 0) selected = 3;

    content = classes[selected];
}

bool ClassSelect::handleEvent(const sf::Event& event){
    if (!event.is<sf::Event::KeyPressed>())
        return false;

    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()){
        checkKeyboardInput(keyPressed->code);
        return true;
    }

    return false;
}


void ClassSelect::render(sf::RenderWindow& window, const sf::Font& font, float time, float deltaTime){
    constexpr float speed = 25.f;
    const float alpha = std::clamp(speed * deltaTime, 0.f, 1.f);

    cursor_rx = utils::lerp(cursor_rx, selected * 128.f + 42.f, alpha);

    sf::RectangleShape keyboardCursor({128.f,312.f});

    keyboardCursor.setFillColor(sf::Color::Transparent);
    keyboardCursor.setOutlineColor(sf::Color::Blue);
    keyboardCursor.setOutlineThickness(3.f);

    keyboardCursor.setPosition({
        roundf(cursor_rx * 1.f) + 16.f,
        96.f
    });

    sf::Text classNameText(font);
    classNameText.setString(content);
    classNameText.setCharacterSize(32);

    auto classNameTextBounds = classNameText.getLocalBounds();

    classNameText.setOrigin({
        classNameTextBounds.position.x + classNameTextBounds.size.x / 2.f,
        classNameTextBounds.position.y + classNameTextBounds.size.y / 2.f
    });
    classNameText.setPosition({320.f, 64.f});
    window.draw(classNameText);


    sf::Text classDescriptionText(font);
    classDescriptionText.setString(class_desc[selected]);
    classDescriptionText.setCharacterSize(22);

    auto classDescriptionTextBounds = classDescriptionText.getLocalBounds();

    classDescriptionText.setOrigin({
        classDescriptionTextBounds.position.x + classDescriptionTextBounds.size.x / 2.f,
        classDescriptionTextBounds.position.y + classDescriptionTextBounds.size.y / 2.f
    });
    classDescriptionText.setPosition({320.f, 440.f});
    window.draw(classDescriptionText);




    window.draw(keyboardCursor);
}