#pragma once
#include "Position.h"
#include <iostream>
class PlayablePosition : public Position
{
public:
	PlayablePosition() {
		row = 0;
		piece = 0;
		col = 0;
	}
	bool canPlay() {
		return true;
	}
	char getPiece() {
		return piece;
	}
	void setPiece(char piece) {
		this->piece = piece;
	}

private:
	int row, col;
	char piece;
};

