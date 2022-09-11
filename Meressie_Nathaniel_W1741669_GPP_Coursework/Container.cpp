#include <iostream>
#include "Player.h"
#include "Container.h"

using namespace std;

//constructor
Container::Container(const string &n, const string &d) : Item(n, d) 
{
	opened = false;
}

//boolean to open item
bool Container::open(Player* p)
{
	//if the item is has already been opened
	if (opened)
	{
		cout << "You've already opened " << getName() << "!" << endl;

		return false;
	}

	//reads inventory to check whether or not the user has the key
	bool hasKey = false;
	for (size_t i = 0; i < key_items.size(); i++)
	{
		//if so then sets key value to true
		if (p->hasItem(key_items[i]))
		{
			hasKey = true;
		}
	}

	//if they dont have key
	if (!hasKey)
	{
		cout << "YOU DO NOT POSSESS THE ITEM TO OPEN THIS LOCKED ITEM! You need a ";

		for (size_t i = 0; i < key_items.size(); i++)
		{
			cout << key_items[i] << endl;
		}

		return false;
	}

	//if they have the key 
	cout << "Ouhhh you have successfully opened your " << getName() << "Lets see what you get! You get: ";

	//adds the items in the container into inventory
	for (size_t i = 0; i < contents.size(); i++)
	{
		p->addItem(contents[i]);
		cout << "| " << contents[i] << " | "; // prints the out item by item
	}

	cout << "" << endl;

	//clears items in container
	contents.clear();
	return true;
}

//adds the key into 
void Container::addKey(const string& k)
{
	key_items.push_back(k);
}

//function that gets called back... that adds the item/s in the container into the users inventory
void Container::addItem(const string &it) 
{
	contents.push_back(it); 
}

//boolean that returns true if its a container
bool Container::isContainer() 
{
	return true;
}

