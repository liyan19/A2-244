#include "Player.h"
Player::Player() {
	name = " ";
	color = 0;
}
Player::Player(std::string name, char color) {
	this->name = name;
	this->color = color;
}

char Player::getColor() {
	return color;
}
void Player::setColor(char color) {
	this->color = color;
}

std::string Player::getName() {
	return name;
}
void Player::setName(std::string name) {
	this->name = name;
}
