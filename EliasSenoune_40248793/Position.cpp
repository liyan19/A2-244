#include "Position.h"
Position::Position() {
	row = 0;
	col = 0;
	piece = 0;

}
Position::Position(int row, int col, char piece) : row(row), col(col), piece(piece) {}

bool Position::canPlay() {
	return true;

}
//getter and setter
char Position::getPiece() {
	return piece;
}
void Position::setPiece(char piece) {
	this->piece = piece;
}
