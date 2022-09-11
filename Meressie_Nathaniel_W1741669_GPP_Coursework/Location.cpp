#include <iostream>
#include "Item.h"
#include "Location.h"

using namespace std;

// gets the key
string Location::getKey(const string& d) const
{
	map<string, string>::const_iterator it = key_items.begin();
	while (it != key_items.end())
	{
		if (it->first == d)
		{
			return it->second;
		}

		it++;
	}

	return "";
}

Location::Location(int no, string n, string d) 
{
	this->number = no;
	this->name = n;
	this->description = d;
}

// maps out the connections between locations
int Location::getConnection(const string& d)
{
	map<string, int>::iterator it = connections.begin();
	while (it != connections.end())
	{
		if (it->first == d)
		{
			return it->second;
		}

		it++;
	}
	return -1;
}

void Location::Connection(string d, int lno, string k)
{
	connections[d] = lno;
	key_items[d] = k;
}

//gets the name of location
string Location::getName() const
{
	return name;
}

//gets the number of the location
int Location::getNumber() const 
{
	return number;
}

//once the user takes an item from location it erares it from the location ( so it cant be taken again )
Item* Location::takeitem(const string& it)
{
	for (size_t i = 0; i < contents.size(); i++)
	{
		if (contents[i]->getName() == it)
		{
			Item* item = contents[i];
			contents.erase(contents.begin() + i);
			return item;
		}
	}

	return nullptr;
}

// add item to the location on the event where the user drops an item
void Location::addItem(Item* it)
{
	contents.push_back(it);
}

//gets the descripion of the location
string Location::getDescription() const 
{
	return description;
}

//prints the items at the location
void Location::print() const
{
	for (size_t i = 0; i < contents.size(); i++)
	{
		cout << "|" << contents[i]->getName() << "| ";
	}

	cout << endl;
}

// drops item
void Location::dropitem(Item *it)
{
	contents.push_back(it);
}