// Exercice IO 2.1
// Written by Léon Chabbey

#include <SFML/Graphics.hpp>
#include <iostream>
#include "json.hpp"
#include "defines.h"
#include "monster.h"


int main() {
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");
	window.setFramerateLimit(30);
	sf::Time dt, elapsedTime;
	sf::Clock clock;

	bool firstMonsterAttacking = true, firstRound = true;
	
	Monster* monster1 = new Monster("../data/monster1.json", sf::Vector2f(10.f, 60.f));
	Monster* monster2 = new Monster("../data/monster2.json", sf::Vector2f(300.f, 60.f));
	monster1->setEnemy(monster2);
	monster2->setEnemy(monster1);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}


		if (firstRound) {
			firstMonsterAttacking = monster1->getSpeed() > monster2->getSpeed() ? true : false;
			firstRound = false;
		}
			

		if (monster1->getMonsterState() == MonsterState::IDLE &&
			monster2->getMonsterState() == MonsterState::IDLE) {

			if (firstMonsterAttacking)
				monster1->setMonsterState(MonsterState::ATTACKING);
			else
				monster2->setMonsterState(MonsterState::ATTACKING);

			firstMonsterAttacking = !firstMonsterAttacking;
		}
			

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