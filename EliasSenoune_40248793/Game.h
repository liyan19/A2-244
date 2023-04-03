#pragma once
#include "Player.h"
#include "Board.h"

class Game
{
public:
	Game();
	Game(Player p1, Player p2);

	void start();


private:
	Board board;
	int starts = 0;
	Player p1;
	Player p2;
};

