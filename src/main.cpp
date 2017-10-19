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
	bool firstMonsterAttacking = true;
	
	Monster* monster1 = new Monster("../data/monster1.json");
	Monster* monster2 = new Monster("../data/monster2.json");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (firstMonsterAttacking)
			monster1->attack(*monster2);

		monster1->update();
		monster2->update();
		window.clear();
		monster1->draw(window);
		monster2->draw(window);
		window.display();
	}

	delete monster1;
	delete monster2;
	return 0;
}