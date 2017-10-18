#ifndef MONSTER_H
#define MONSTER_H

#include "SFML\Graphics.hpp"
#include <string>

enum class Race {
	ORC,
	GOBLIN,
	TROLL,
	LENGTH
};

class Monster {
private:
	double health,
		attackPower,
		defensivePower,
		speed;
	Race race;
	sf::Sprite sprite;
	sf::Texture texture;
public:
	Monster(std::string);

	void attack();

	sf::Sprite getSprite();

	~Monster();
};


#endif // !MONSTER_H
