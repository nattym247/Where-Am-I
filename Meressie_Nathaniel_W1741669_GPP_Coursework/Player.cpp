#include <iostream>
#include "Player.h"
#include "Location.h"
#include "Item.h"
#include "Container.h"

using namespace std;

Player::Player(Location *l) 
{
	this->location = l;
	targetLocation = 0;
	steps = 0;
}

// Setting a boolean to return whether or not the user current location is the targetlocation, so so then game has been completed....
bool Player::Won()
{
	return location->getNumber() == targetLocation;
}

// Function for adding a item to inventory
void Player::addItem(const string& it)
{
	inventory.push_back(it); //adds item to inventory
}

// Function for getting an item/s
Item* Player::getItem(string i)
{
	map<string, Item*>::iterator it = items.begin();

	//loop to check all items in list (inventory)
	while (it != items.end())
	{
		if (i == it->second->getName())
		{
			return it->second;
		}

		it++;
	}

	return nullptr;
}

// Setter for location
void Player::setLocation(Location* l)
{
	this->location = l;
}

// Getter for location
Location* Player::getLocation() const
{
	return location;
}

// Print function for users status in game
void Player::Print() const
{
	cout << "" << endl;
	cout << "You are " << location->getName() << "!" << endl; // Prints current location name 
	cout << "Location Description: " << location->getDescription() << endl; // Prints current location description
	cout << "Location Contents: "; // Prints current location contents 
	location->print(); // Calls function from location class
	cout << "" << endl;
	// Prints out character inventory
	cout << "Inventory - ";

	// Loop that gets all the items in users inventory,
	for (size_t i = 0; i < inventory.size(); i++)
	{
		cout << "| " << inventory[i] << " | "; // prints the out item by item
	}

	// if statement checking whether or not inventory has items  
	if (inventory.size() == 0)
	{
		cout << "No items!" << endl;
	}

	cout << "" << endl;
}

// move function
bool Player::Move(const string& d)
{
	int number = location->getConnection(d);

	// if loctaion does not exist
	if (number == -1)
	{
		cout << "" << endl;
		cout << "YOU CANNOT GO THAT WAY! MUHAHAHA " << endl;

		return false;
	}

	else
	{
		string key = location->getKey(d);

		//if user does not own the key
		if (key != "" && !hasItem(key))
		{
			cout << "" << endl;
			cout << "YOU DO NOT POSSES THE KEY, TO ENTER HERE! FIND THE KEY THEN COME BACK! " << endl;

			return false;
		}

		Location* loc = getLocation(number);
		setLocation(loc);

		//prints print function... to show users status in the game after everymove
		this->Print();

		return true;
	}
}

// Getter for location
Location* Player::getLocation(int no)
{
	map<int, Location*>::iterator it = locations.begin();

	while (it != locations.end())
	{
		if (no == it->second->getNumber())
		{
			return it->second;
		}

		it++;
	}

	return nullptr;
}

// boolean for taking an item... if item is their it'll successfull take it.. else it'll reject the command
bool Player::takeItem(const string& it)
{
	Item* item = location->takeitem(it);

	if (item != nullptr)
	{
		inventory.push_back(item->getName());

		cout << "Success, " << it << " has been added to your inventory." << endl;

		return true;
	}

	else
	{
		cout << "Ah, the item you seek is not at this location." << endl;
		return false;
	}
}

// boolean for dropping an item... if item is in inventory then it'll successfull drop it.. else it'll reject the command
bool Player::dropItem(const string& it)
{
	int index = -1;

	for (size_t i = 0; i < inventory.size(); i++)
	{
		if (inventory[i] == it)
		{
			index = i;
		}
	}

	if (index == -1)
	{
		cout << "Unfortunately, " << it << " is not in your inventory!" << endl;

		return false;
	}

	else
	{
		location->addItem(getItem(it));
		inventory.erase(inventory.begin() + index);
		cout << "Seems you have dropped a " << it << " at this location." << endl;

		return true;
	}
}

// boolean that checks wherther or not the user has the item/key
bool Player::hasItem(const string &it) const 
{
	for (size_t i = 0; i < inventory.size(); i++) 
	{
		if (inventory[i] == it) 
		{
			return true;
		}
	}

	return false;
}

// boolean that first checks whether or not item can be open, if so it'll recieve all the items in the container
bool Player::openItem(const string &it) 
{
	int index = -1;

	for (size_t i = 0; i < inventory.size(); i++) 
	{
		if (inventory[i] == it) 
		{
			index = i;
		}
	}

	if (index == -1) {
		cout << "Unfortunately, " << it << " is not in your inventory!" << endl;

		return false;
	} 
	
	else 
	{
		Item *item = getItem(it);
		Container *container = dynamic_cast<Container*>(item);

		if (container != NULL) 
		{
			return container->open(this);
		} 
		
		else 
		{
			cout << "Unfortunately, " << it << " cannot be open!" << endl;

			return false;
		}
	}
}

// setter for map
void Player::setMap(map<string, Item*> i, map<int, Location*> lno) 
{
	this->locations = lno;
	this->items = i;

	map<int, Location*>::iterator it = locations.begin();

	while (it != locations.end()) 
	{
		targetLocation = it->second->getNumber();
		it++;
	}
}