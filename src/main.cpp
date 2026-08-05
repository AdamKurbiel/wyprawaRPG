/*
<Copyright Adam Kurbiel 2026>

Main file. Currently searching for some kind of scene/ui/render manager that will
handle all updates, renders and checks.

*/
#include <SFML/Graphics.hpp>
#include "Prefabs/characterCreation.hpp"
#include "Systems/ResourceManager.hpp"
#include "game.hpp"


int main()
{
	ResourceManager rm;
	sf::RenderWindow window( sf::VideoMode( { 640, 512 } ), "wyprawaRPG", sf::Style::Titlebar | sf::Style::Close);

	Character character;
	Game game;

	character.set_class(rm,window);
	character.set_name(rm,window);
	game.run(rm, window, character);

	return 0;
};