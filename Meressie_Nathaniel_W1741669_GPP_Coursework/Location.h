#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Item.h"

using namespace std;

class Item;

class Location 
{
	// Location number.
	int number;

	// Location name.
	string name;

	// Location description. 
	string description;

	// Items currently in this location. 
	vector<Item*> contents;

	// For each possible direction, the location reached and item required (if any). 
	map<string, string> key_items; 
	map<string, int> connections; 
public:

	// Constructor.
	Location(int no, string n, string d);

	int getConnection(const string& d);

	// Try to take an item. 
	Item* takeitem(const string& it);

	string getKey(const string& direction) const;

	// Place an item in this location.
	void dropitem(Item* it);

	// Getters and setters. 
	int getNumber() const;
	string getName() const;
	string getDescription() const;

	void print() const;

	void addItem(Item* it);
	void Connection(string d, int lno, string k);

};