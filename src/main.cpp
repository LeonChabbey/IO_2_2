// Exercice IO 2.1
// Written by Léon Chabbey

#include <SFML/Graphics.hpp>
#include <iostream>
#include "json.hpp"
#include "defines.h"
#include "monster.h"


int main() {
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");
	window.setFramerateLimit(60);
	
	Monster* monster1 = new Monster("../data/monster1.json");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		monster1->draw(window);
		window.display();
	}

	delete monster1;
	return 0;
}