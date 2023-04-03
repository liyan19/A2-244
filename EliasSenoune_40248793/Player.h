#pragma once
#include <string>
class Player
{
public:

	Player();
	Player(std::string name, char color);
	std::string getName();
	void setName(std::string name);
	char getColor();
	void setColor(char color);
	bool operator==(const Player& other) const {			//https://stackoverflow.com/questions/2194762/how-to-compare-two-objects-the-calling-object-and-the-parameter-in-a-class
		return (name == other.name && color == other.color);
	}
private:
	std::string name;
	char color;
};

