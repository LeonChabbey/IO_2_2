#ifndef MONSTER_H
#define MONSTER_H

#include "SFML\Graphics.hpp"
#include <string>
#include <map>
#include "defines.h"

enum class Race;
struct RaceConfig;

class Monster {
private:
	double health,
		attackPower,
		defensivePower,
		speed;
	Race race;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Text healthUI;

	bool validateRace(int);
public:
	Monster(std::string);

	void attack(Monster&);
	void setHealthUI();

	sf::Sprite getSprite();

	void update();
	void draw(sf::RenderWindow&);
	~Monster();
};

RaceConfig getRaceConfig(Race&);


#endif // !MONSTER_H
