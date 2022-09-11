#include <iostream>
#include "Item.h"

Item::~Item()
{
}

Item::Item(string n, string d) : name(n), description(d) 
{
}

//gets the item description
string Item::getDescrioption() const
{
	return description;
}

//gets the item name
string Item::getName() const 
{
	return name;
}

//boolean to check whether or not the item is a container 
bool Item::isContainer() 
{
	return false;
}
