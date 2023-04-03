// A2 prog.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Board.h"
#include "Game.h"
#include <windows.h>
using namespace std;

int main()
{

    Player p1("", Position::WHITE);
    Player p2("", Position::BLACK);
    Game g1(p1, p2);

}

