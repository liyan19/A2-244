#pragma once
#include "Position.h"
#include "Player.h"
#include <string>
#include <vector>
#include "PlayablePosition.h"
class Board
{
public:
	Board();
	void drawBoard();
	static Board loadBoard();
	Board(int start, Player p1, Player p2);
	void play();
	static const int SIZE = 8;
	Position board[SIZE][SIZE];
	void makeMove(int row, int col);
	Board(std::string file_name);
	void flipPiece(int row, int col);
	std::vector<std::vector<int>> findGoodMove();
	bool isFlippable(int row, int col);
	void concede();
	void checkWin();
	void checkWin2();

private:
	void switchPlayer();
	void save();
	Player p1;
	Player p2;
	Player curr;





};
