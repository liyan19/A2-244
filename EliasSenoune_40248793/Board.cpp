#include "Board.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
Board::Board() {

}
//Board constructor
Board::Board(int start, Player p1, Player p2) {
	using namespace std;

	this->p1 = p1;
	this->p2 = p2;
	this->curr = p1;
	//fills the board with empty positions
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			board[i][j] = Position(i, j, Position::EMPTY);
		}
	}
	//starting positions
	if (start == 1) {
		board[3][3].setPiece(Position::WHITE);
		board[3][4].setPiece(Position::BLACK);
		board[4][3].setPiece(Position::BLACK);
		board[4][4].setPiece(Position::WHITE);
		board[3][7].setPiece(Position::UNPLAYABLE);
		board[4][7].setPiece(Position::UNPLAYABLE);
	}
	else if (start == 2) {
		board[2][2].setPiece(Position::WHITE);
		board[2][3].setPiece(Position::WHITE);
		board[2][4].setPiece(Position::BLACK);
		board[2][5].setPiece(Position::BLACK);
		board[3][2].setPiece(Position::WHITE);
		board[3][3].setPiece(Position::WHITE);
		board[3][4].setPiece(Position::BLACK);
		board[3][5].setPiece(Position::BLACK);
		board[4][2].setPiece(Position::BLACK);
		board[4][3].setPiece(Position::BLACK);
		board[4][4].setPiece(Position::WHITE);
		board[4][5].setPiece(Position::WHITE);
		board[5][2].setPiece(Position::BLACK);
		board[5][3].setPiece(Position::BLACK);
		board[5][4].setPiece(Position::WHITE);
		board[5][5].setPiece(Position::WHITE);
		board[3][7].setPiece(Position::UNPLAYABLE);
		board[4][7].setPiece(Position::UNPLAYABLE);
	}

}



void Board::drawBoard() {
	system("CLS");

	
	std::cout << "Player 1 " << "(" << p1.getColor() << "): " << p1.getName() << std::endl;
	std::cout << "Player 2 " << "(" << p2.getColor() << "): " << p2.getName() << std::endl;
	std::cout << "Current player " << "(" << curr.getColor() << "): " << curr.getName() << std::endl;
	for (int i = 0; i < SIZE; i++) {
		std::cout << i << " ";
	}
	std::cout << std::endl;
	for (int i = 0; i < SIZE; i++) {

		for (int j = 0; j < SIZE; j++) {
			char piece = board[i][j].getPiece();
			std::cout << piece << " ";
		}
		std::cout << i << " " << std::endl;

	}
	std::cout << std::endl;
	for (auto& move : findGoodMove()) {
		std::cout << "[" << move[0] << ", " << move[1] << "] ";
	}
	std::cout << std::endl;


}

void Board::save() {
	std::string save_file;
	std::cout << "Choose save file: 1	2	3	 " << std::endl;
	std::cin >> save_file;
	save_file.append(".txt");
	std::ofstream file(save_file);
	if (file.is_open()) {

		file << p1.getColor() << " " << p1.getName() << std::endl;
		file << p2.getColor() << " " << p2.getName() << std::endl;
		file << curr.getColor() << " " << curr.getName() << std::endl;
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				char piece = board[i][j].getPiece();
				file << piece;
			}
			
		}
		file.close();
	}
	exit(0);
}

void Board::flipPiece(int row, int col) {
	char otherPlayer;
	if (curr.getColor() == Position::BLACK) otherPlayer = Position::WHITE;
	else  otherPlayer = Position::BLACK;
	std::vector<std::vector<int>> pieceToFlip;
	//find every positions around the position.
	for (int i = -1; i <= 1;i++) {
		for (int j = -1; j <= 1; j++) {
			if (i == 0 && j == 0)continue;
			int nextX = row + i;
			int nextY = col + j;
			//make sure the value doesn't go out of bound
			if (nextX > 7 || nextX < 0 || nextY> 7 || nextY < 0) { continue; }
			char nextValue = board[nextX][nextY].getPiece();
			bool flipthat = false;
			//check if the piece next to the placed piece is different from it and if it is check every piece in that direction until it is the same as the placed piece
			if (nextValue == otherPlayer) {
				while (nextValue == otherPlayer)
				{
					nextX += i;
					nextY += j;
					if (nextX > 7 || nextX < 0 || nextY> 7 || nextY < 0) { break; }
					nextValue = board[nextX][nextY].getPiece();
				}
				//return true if there's a piece of the same color in that direction after at least one piece of the other color
				if (nextValue == curr.getColor()) { flipthat = true; }
				if (flipthat) {
					nextX = row + i;
					nextY = col + j;
					nextValue = board[nextX][nextY].getPiece();
					while (nextValue == otherPlayer)
					{
						//puts the values between the placed piece and the piece found at the end of the direction in a vector
						std::vector<int> disc = { nextX, nextY };
						pieceToFlip.push_back(disc);
						nextX += i;
						nextY += j;


						nextValue = board[nextX][nextY].getPiece();
					}
				}
			}

		}
	}
	//flip the pieces at the position inside the vector
	for (auto &pos : pieceToFlip) {
		board[pos[0]][pos[1]].setPiece(curr.getColor());

	}


}
//check if the position can flip pieces. Return true if a move flips other pieces. Returns false otherwise
bool Board::isFlippable(int row, int col) {
	//char otherPlayer = (curr.getColor() == Position::BLACK) ? Position::WHITE : Position::BLACK;
	char otherPlayer;
	if (curr.getColor() == Position::BLACK) otherPlayer = Position::WHITE;
	else  otherPlayer = Position::BLACK;
	for (int i = -1; i <= 1;i++) {
		for (int j = -1; j <= 1; j++) {
			if (i == 0 && j == 0)continue;
			if (row + i > 7 || row + i < 0 || col + j > 7 || col + j < 0) {
				continue;
			}
			char nextValue = board[row +i][col + j].getPiece();
			if (nextValue == otherPlayer) {
				int nextX = row + i;
				int nextY = col + j;
				while (nextValue == otherPlayer) {
					nextX += i;
					nextY += j;
					if (nextX > 7 || nextX < 0 || nextY>7 || nextY < 0) {
						break;
					}
					nextValue = board[nextX][nextY].getPiece();
				}
				if (nextValue == curr.getColor()) {
					return true;
				}
			}
		}
	}
	return false;
}

void Board::takeTurn() {
	if (p1 == curr) {
		this->curr = p2;
	}
	else
	{
		this->curr = p1;
	}
}
//returns the loaded board
Board Board::loadBoard() {
	std::string save_file;
	std::cout << "Choose a save file: 1		2		3" << std::endl;
	std::cin >> save_file;
	Board board(save_file.append(".txt"));
	return board;

}

Board::Board(std::string save_file) {
	std::vector<char>colorVec;
	std::vector<std::string>nameVec;
	std::ifstream file(save_file);
	std::string line, name, boardString;
	char color;
	//First three lines are for the players and put the name and color of the each player in a vector
	for (int i = 0; i < 3; i++) {
		std::getline(file, line);
		std::stringstream ss(line);
		ss >> color >> name;
		if (color == 'W')color = Position::WHITE;
		else { color = Position::BLACK; }
		colorVec.push_back(color);
		nameVec.push_back(name);
	}
	//sets the values for each players
	p1.setColor(colorVec[0]);
	p1.setName(nameVec[0]);
	p2.setColor(colorVec[1]);
	p2.setName(nameVec[1]);
	curr.setColor(colorVec[2]);
	curr.setName(nameVec[2]);
	//transform the line which represents the board into a 2D array of Position
	int k = 0;
	std::getline(file, boardString);
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			board[i][j] = Position(i, j, Position::EMPTY);
			board[i][j].setPiece(boardString[k]);
			k++;
		}
	}


}
void Board::concede() {
	takeTurn();
	std::cout << "You've conceded. " << "GG! " << curr.getName() << "(" << curr.getColor() << ") won the game! " << std::endl;
	exit(0);
}
void Board::makeMove(int row, int col) {
	board[row][col].setPiece(curr.getColor());
	flipPiece(row, col);
}

//Find legal moves and put them in a vector
std::vector<std::vector<int>> Board::findGoodMove() {
	std::vector<std::vector<int>> goodMoveList;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (board[i][j].getPiece() == Position::EMPTY) {
				if (isFlippable(i, j)) {

					std::vector<int> move = { i,j };
					goodMoveList.push_back(move);



					//sort(goodMoveList.begin(), goodMoveList.end());			//https://stackoverflow.com/questions/1041620/whats-the-most-efficient-way-to-erase-duplicates-and-sort-a-vector
					//goodMoveList.erase(unique(goodMoveList.begin(), goodMoveList.end()), goodMoveList.end());
				}
			}
		}
	}

	return goodMoveList;
}
//Loops through every value of the board and if the board is filled. If it is count the amount of piece for each player and display a message accordingly.
void Board::checkWin() {
	int whiteCount = 0, blackCount = 0, emptyCount = 0;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {

			if (board[i][j].getPiece() == Position::WHITE) whiteCount++;
			else if (board[i][j].getPiece() == Position::BLACK)blackCount++;
			else if (board[i][j].getPiece() == Position::EMPTY)emptyCount++;
		}
	}
	if (emptyCount == 0) {
		if (whiteCount > blackCount) std::cout << "GG! Player 1: " << p1.getName() << " (" << p1.getColor() << ") won the game! " << std::endl;
		else if (blackCount > whiteCount) std::cout << "GG! Player 2: " << p2.getName() << " (" << p2.getColor() << ") won the game!" << std::endl;
		else std::cout << "A game of othello when played perfectly alway end in a tie. GG to " << p1.getName() << " (" << p1.getColor() << ") and " << p2.getName() << " (" << p2.getColor() << ")! " << " Game ended in a tie." << std::endl;
		exit(0);
	}

}
//If both players have no legal moves count the amount of piece for each player and display a message accordingly.
void Board::checkWin2() {
	if (findGoodMove().empty()) {
		takeTurn();
		if (findGoodMove().empty()) {
			int whiteCount = 0, blackCount = 0, emptyCount = 0;
			for (int i = 0; i < SIZE; i++) {
				for (int j = 0; j < SIZE; j++) {

					if (board[i][j].getPiece() == Position::WHITE) whiteCount++;
					else if (board[i][j].getPiece() == Position::BLACK)blackCount++;
					else if (board[i][j].getPiece() == Position::EMPTY)emptyCount++;
				}
			}
			if (whiteCount > blackCount) std::cout << "GG! Player 1: " << p1.getName() << " (" << p1.getColor() << ") won the game! " << std::endl;
			else if (blackCount > whiteCount) std::cout << "GG! Player 2: " << p2.getName() << " (" << p2.getColor() << ") won the game!" << std::endl;
			else std::cout << "A game of othello when played perfectly alway end in a tie. GG to" << p1.getName() << " (" << p1.getColor() << ") and " << p2.getName() << " (" << p2.getColor() << ")" << " game ended in a tie" << std::endl;
			exit(0);
		}
		takeTurn();
	}
}
void Board::play() {

	std::string save_file;
	int choice;
	p1.setColor(Position::WHITE);
	p2.setColor(Position::BLACK);

	drawBoard();

	//game loop
	while (true) {
		bool validMove = false;
		int row = 0, col = 0;
		checkWin2();
		//check if no moves available
		if (findGoodMove().empty()) {
			//menu for when no moves available
			std::cout << "You have no more move make a choice: " << std::endl;
			std::cout << "1. Save the game" << std::endl;
			std::cout << "2. Concede the game" << std::endl;
			std::cout << "3. Skip this turn" << std::endl;
			std::cin >> choice;

			switch (choice) {
			case 1:
				save();
				break;
			case 2:
				concede();
				break;
			case 3:
				std::cout << "You've skipped this turn. " << std::endl;
				break;
			default:
				break;
			}
		}
		else
		{
			//menu to make moves
			std::cout << "You have moves make a choice: " << std::endl;
			std::cout << "1. Save the game" << std::endl;
			std::cout << "2. Concede the game" << std::endl;
			std::cout << "3. Make a move" << std::endl;
			std::cin >> choice;

			switch (choice) {
			case 1:
				save();
				break;
			case 2:
				concede();
				break;
			case 3:
				//Input row and colum
				while (!validMove) {
					std::cout << "Enter row: " << std::endl;
					std::cin >> row;
					std::cout << "Enter column: " << std::endl;
					std::cin >> col;

					for (auto move : findGoodMove()) {
						if (move[0] == row && move[1] == col) {	
							validMove = true;
							break;
						}
					}
					if (!validMove) {
						std::cout << "Try again" << std::endl;
					}
				}
				makeMove(row, col);
				break;
			default:

				break;
			}
		}
		takeTurn();
		drawBoard();
		checkWin();
	}

}
