#pragma once
#include "Item.h"
#include "Location.h"
#include <iostream>
#include <vector>

using namespace std;

class Player 
{
	int targetLocation;

	// Player's inventory.
	vector<string> inventory;
	map<int, Location*> locations;

	// Player's current location. 
	Location* location;

	map<string, Item*> items;
	
public:

	void setMap(map<string, Item*> i, map<int, Location*> l);

	Player(Location *l);

	bool Won();

	// Add item to inventory. 
	void addItem(const string& it);

	Item* getItem(string i);

	// Getter and setter.
	Location* getLocation() const;
	void setLocation(Location* it);

	// Print the current location, inventory, and number of steps. 
	void Print() const;

	// Try to go in the given direction. 
	bool Move(const string& d);

	Location* getLocation(int lno);

	// Try to take the item.
	bool takeItem(const string& it);
	// Try to drop the item.
	bool dropItem(const string& it);
	// Check whether the player has the item.
	bool hasItem(const string& it) const;
	// Try to open the item. 
	bool openItem(const string& it);

	// Number of steps taken so far.
	int steps = 1;

	string Playername;
};

