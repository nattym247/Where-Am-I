#pragma once
#include "Player.h"
#include "Container.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <map>
#include "Item.h"
#include <cstdlib>
#include "Location.h"

using namespace std;

// Auxiliary class containing game state data. 
class Game 
{
	Player* p;

	// Keeps hold of location numbers/status
	vector<int> locationNumbers;
	vector<string> itemNames;

	// Keeps track of known locations by number.
	map<int, Location*> locations;

	map<string, Item*> items;

public:

	static string Playername;

	// Auxiliary function: replaces all upper-case letters with lower-case version.
	string toLower(string s);

	vector<string> Split(string s, char c);

	string Cut(string s);

	~Game();

	Game(string f);

	// Parses the game data.
	void Parsedata(string i, string &a, string &t);

	// Parses and executes a command input by the player.
	void Play();

	void Register();

	void PlayAgain();

	void LocationFunct(const string& f);

};
