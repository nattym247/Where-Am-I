#pragma once
#include <vector>

using namespace std;

#include "Item.h"

class Player;

class Container: public Item 
{
	// Contents of this container. 
	vector<string> contents;

	// Items needed to open this container.
	vector<string> key_items;

	// Keeps track of whether this container has already been opened. 
	bool opened;
public:
	// Constructor. 
	Container(const string& n, const string& d);

	// Adds an item to the contents.
	void addItem(const string &it);

	// Adds a key item. 
	void addKey(const string &k);

	// Tries to open this container.
	bool open(Player *p);

	bool isContainer();
};
