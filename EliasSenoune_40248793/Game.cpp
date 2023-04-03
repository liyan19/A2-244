#include "Game.h"
#include "Player.h"
#include <iostream>
Game::Game() {}

Game::Game(Player p1, Player p2) {
	this->p1 = p1;
	this->p2 = p2;
	int choice;
	std::cout << "Welcome " << std::endl;
	std::cout << "1. Load a Game" << std::endl;
	std::cout << "2. Quit" << std::endl;
	std::cout << "3. Start New Game" << std::endl;

	std::cin >> choice;
	switch (choice)
	{
	case 1:

		board = Board::loadBoard();
		board.play();

		break;
	case 2:
		std::cout << "Quitting game..." << std::endl;
		exit(0);
		break;
	case 3:

		start();
		break;
	default:
		break;
	}


}
void Game::start() {

	std::string name;
	std::cout << "You've chosen to create a new game. \n Enter your name Player 1: " << std::endl;
	std::cin >> name;
	p1.setName(name);
	std::cout << "Enter your name Player 2: " << std::endl;
	std::cin >> name;
	p2.setName(name);
	
	std::cout << "Choose starting board 1 or 2" << std::endl;
	std::cin >> starts;
	board = Board(starts, p1, p2);
	board.play();


}
