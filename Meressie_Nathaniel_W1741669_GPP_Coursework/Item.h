#pragma once
#include <string>
#include <iostream>
#include <map>

using namespace std;

class Item 
{
	// The item's name. 
	string name;
	// The item's description. Required.
	string description;
public:
	// Constructor.
	Item(string n, string d);

	// Getter methods. Required.
	string getName() const;
	string getDescrioption() const;

	// Virtual base methods for container operations.
	virtual bool isContainer();
	virtual ~Item();

};

