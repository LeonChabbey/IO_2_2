#include "monster.h"
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include "json.hpp"
#include "defines.h"

using json = nlohmann::json;


struct RaceConfig {
	std::string name;
	std::string fileName;
};


RaceConfig getRaceConfig(Race& race) {
	RaceConfig raceConfig;
	switch (race) {
	case Race::ORC:
		raceConfig.name = "Orc";
		raceConfig.fileName = "orc.png";
		break;
	case Race::GOBLIN:
		raceConfig.name = "Goblin";
		raceConfig.fileName = "goblin.png";
		break;
	case Race::TROLL:
		raceConfig.name = "Troll";
		raceConfig.fileName = "troll.png";
		break;
	}
	return raceConfig;
}


/////////////////////////////
/////// Monster Class ///////
/////////////////////////////

Monster::Monster(std::string filePath, sf::Vector2f startingPosition) {
	std::ifstream i(filePath);
	json data;
	i >> data;

	int chosenRace = data["race"] - 1;

	if (chosenRace < (int)Race::LENGTH && chosenRace >= 0)
		race = Race(chosenRace);
	else {
		race = Race(0);
		std::cout << "Race not valid, therefore using default '" << getRaceConfig(race).name << "'" << std::flush;
	}

	health = data["health"];
	attackPower = data["attackPower"];
	defensivePower = data["defensivePower"];
	speed = data["speed"];
	startingPos = startingPosition;
	state = MonsterState::IDLE;

	// Texture/Sprite
	std::string textureName = getRaceConfig(race).fileName;
	texture.loadFromFile(IMG_FOLDER_PATH + textureName);
	sprite.setTexture(texture);
	sprite.scale(0.1,0.1);
	sprite.setPosition(startingPos);
	
	//HP Text
	std::string fontPath = std::string(FONT_FOLDER_PATH) + std::string(DEFAULT_FONT);

	if (!font.loadFromFile(fontPath))
	{
		std::cout << "ERROR: Cannot load font" << std::flush;
	}

	healthUI.setFont(font);
	healthUI.setCharacterSize(24);
	healthUI.setFillColor(sf::Color::Red);
}

sf::Vector2f Monster::goToPosition(const sf::Vector2f& pointA, const sf::Vector2f& pointB, float speed) {
	if (speed > 1.f)
		speed = 1.f;

	else if (speed < 0.f)
		speed = 0.f;

	return pointA + (pointB - pointA) * speed;
}

void Monster::attack() {

	if (enemy == nullptr) {
		state = MonsterState::REPOSITIONING;
	} else {
		std::cout << "blblbl ? : " << (sprite.getPosition() == enemy->getCurrentPosition()) << "\n" << std::flush;
		
		if (sprite.getPosition() == enemy->getCurrentPosition()) {
			double damage = attackPower - enemy->defensivePower;

			if (damage <= 0)
				damage = 1;

			enemy->takeDamage(damage);

			state = MonsterState::REPOSITIONING;
		} else {
			sprite.setPosition(goToPosition(sprite.getPosition(), enemy->getCurrentPosition(), 0.3));
		}

	}
}

void Monster::takeDamage(int damage) {
	if (health - damage < 0)
		health = 0;
	else
		health -= damage;
}

void Monster::repositioningMonster() {
	if (sprite.getPosition() == startingPos)
		state = MonsterState::IDLE;	
	else
		sprite.setPosition(goToPosition(sprite.getPosition(), startingPos, 0.3));
}

void Monster::setMonsterState(MonsterState newState) {
	std::cout << getRaceConfig(race).name << " is set to state::" << (int)state << "\n" << std::flush;
	state = newState;
}

void Monster::setEnemy(Monster* enemy) {
	this->enemy = enemy;
}

MonsterState Monster::getMonsterState() {
	return state;
}

double Monster::getSpeed() {
	return speed;
}

sf::Vector2f Monster::getCurrentPosition() {
	return sprite.getPosition();
}

sf::Sprite& Monster::getSprite() {
	return sprite;
}

void Monster::update() {

	std::cout << getRaceConfig(race).name << " is set to state::" << (int)state << " ///// startingPos: " << startingPos.x << "/" << startingPos.y << " //////// currentPos: "
		<< sprite.getPosition().x << "/" << sprite.getPosition().y << " ///// enemy: " << (int)enemy->getMonsterState() << "////// yay?: " << (sprite.getPosition() == startingPos) << "\n" << std::flush;

	switch (state) {
	case MonsterState::IDLE:
		break;
	case MonsterState::ATTACKING:
		attack();
		break;
	case MonsterState::REPOSITIONING:
		repositioningMonster();
		break;
	}

	healthUI.setString(std::to_string((int)health) + " HP");
	healthUI.setPosition(sf::Vector2f(sprite.getPosition().x - 10.f, sprite.getPosition().y));
}

void Monster::draw(sf::RenderWindow& window) {
	window.draw(healthUI);
	window.draw(sprite);
}

Monster::~Monster() {
}
