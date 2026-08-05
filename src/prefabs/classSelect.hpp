#pragma once

#include <string>
#include <SFML/Graphics.hpp>

class ClassSelect{
private:
    const std::string classes[4] = {"Warrior","Knight","Mage","Archer"};
    const std::string class_desc[4] = {
        "This is an description for the Warrior.",
        "This is an description for the Knight.",
        "This is an description for the Mage.",
        "This is an description for the Archer."};

public:
    bool enabled = true;
    
    std::string selected_str = "";
    int selected = 0;

    std::string content = classes[selected];
    float cursor_rx;

    bool handleEvent(const sf::Event& event);
    void checkKeyboardInput(sf::Keyboard::Key keyCode);

    void render(sf::RenderWindow& window, const sf::Font& font, float time, float deltaTime);
};