#include <iostream>
#include <fstream>
#include <string>
#include "Game.h"
#include "Windows.h"

using namespace std;

int main() 
{
	//Sets console text too \/
	SetConsoleTitle(TEXT("WELCOME TO TEXT ADVENTURE GAME!!!"));

	//Set colour for system. 
	system("Color 09");

	// Creates a game object.
	Game game("DataFile.txt");

	//Runs the play function. Starting game!
	game.Play();

	return 0;
}
