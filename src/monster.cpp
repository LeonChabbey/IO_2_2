#include "monster.h"
#include <fstream>
#include <iostream>
#include <string>
#include "json.hpp"

#define IMG_FOLDER_PATH "../data/img/"

using json = nlohmann::json;

Monster::Monster(std::string filePath) {
	std::ifstream i(filePath);
	json data;
	i >> data;

	std::string textureName = data["texture"];

	texture.loadFromFile(IMG_FOLDER_PATH + textureName);
	sprite.setTexture(texture);
	sprite.setScale(2.f, 2.f);

	health = data["health"];
	attackPower = data["attackPower"];
	defensivePower = data["defensivePower"];
	speed = data["speed"];
	race = Race(data["race"]-1);
}

sf::Sprite Monster::getSprite() {
	return sprite;
}

Monster::~Monster()
{
}
