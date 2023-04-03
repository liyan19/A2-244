#pragma once
class Position
{
public:
	virtual bool canPlay();
	static const char UNPLAYABLE = '*';
	static const char EMPTY = ' ';
	static const char BLACK = 'B';
	static const char WHITE = 'W';
	Position();
	Position(int row, int col, char piece);
	
	char getPiece();
	void setPiece(char piece);

protected:
	char piece;
	int row;
	int col;
};

