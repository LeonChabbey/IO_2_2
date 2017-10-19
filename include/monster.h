#ifndef MONSTER_H
#define MONSTER_H

#include "SFML\Graphics.hpp"
#include <string>
#include <map>
#include "defines.h"

enum class Race {
	ORC,
	GOBLIN,
	TROLL,
	LENGTH
};
struct RaceConfig;
RaceConfig getRaceConfig(Race&);

enum class MonsterState {
	IDLE,
	ATTACKING,
	REPOSITIONING,
	DEAD
};

class Monster {
private:
	double health,
		attackPower,
		defensivePower,
		speed;
	sf::Vector2f startingPos;
	Race race;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Text healthUI;
	sf::Font font;
	MonsterState state;
	
	Monster* enemy = nullptr;

	sf::Vector2f goToPosition(const sf::Vector2f&, const sf::Vector2f&);

public:
	
	Monster(std::string, sf::Vector2f);

	void attack();
	void takeDamage(int);
	void repositioningMonster();
	void monsterDead();

	void setMonsterState(MonsterState);
	void setEnemy(Monster*);

	double getHealth();
	MonsterState getMonsterState();
	double getSpeed();
	sf::Vector2f getCurrentPosition();
	sf::Sprite& getSprite();

	void update();
	void draw(sf::RenderWindow&);
	~Monster();
};


#endif // !MONSTER_H
