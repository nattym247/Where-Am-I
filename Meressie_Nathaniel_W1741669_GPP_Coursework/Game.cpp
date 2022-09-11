#include <iostream>
#include "Game.h"
#include "Player.h"

//game function 
Game::Game(string f)
{
	LocationFunct(f);

	p = new Player(locations.begin()->second);

	//sets the map for the items and location, using the data within the datafile.txt so the user can progress through the game
	p->setMap(items, locations);

	for (size_t i = 0; i < itemNames.size(); i++)
	{
		if (p->getItem(itemNames[i]) == nullptr)
		{
			cout << "" << endl;
			cout << "That is a non-recognised Item " << itemNames[i] << endl;
			exit(0);
		}
	}

	for (size_t i = 0; i < locationNumbers.size(); i++)
	{
		if (p->getLocation(locationNumbers[i]) == nullptr)
		{
			cout << "" << endl;
			cout << "That is a non-recognised location " << locationNumbers[i] << endl;
			exit(0);
		}
	}
}

//function for a help guide, that gets called on to print out for guidance as the user may not know what the controls are
void Controls()
{
	cout << "" << endl;
	cout << "Controls and rules guide:" << endl;
	cout << "Heads up. The general logic the ai this game understands. Written below!" << endl;
	cout << "The aim of this game is to get to the last location. Having the ability to pickup/drop items." << endl;
	cout << "The AI can only understand general commands such as 'look' or 'take Strongbox' or 'drop Strongbox' or 'open Strongbox' or 'quit'!" << endl;
	cout << "The AI can only understand movement commands such as 'north' or 'south' or 'east' or 'west'!" << endl;
	cout << "" << endl;
}

// welcome text function
void WelcomeText()
{
	cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "                                     WELCOME TO MY TEXT BASED ADVENTUR GAME                                           " << endl;
	cout << "----------------------------------------------------------------------------------------------------------------------" << endl;

	Controls();
}

// play again function, where the user gets the option to choose whether or not they'll like to play again
void Game::PlayAgain()
{
	char playagin;

	cout << "" << endl;
	cout << "Would you like to play again?";
	cout << "(Y/N): ";
	cout << "";
	cin >> playagin;

	while (playagin != 'Y' && playagin == 'y' && playagin != 'N' && playagin == 'n')
	{
		cout << "Please Type Y or N: ";
		cin >> playagin;
	}

	if (playagin == 'Y' || playagin == 'y')
	{
		cout << "" << endl;

		Game game("DataFile.txt");

		game.Play();
	}

	if (playagin == 'N' || playagin == 'n')
	{
		cout << "" << endl;
		cout << "Thanks for playing! Goodbye!" << endl;
		cout << "" << endl;
		cout << "Made by Nathaniel! " << endl;

		exit(0);
	}
}

//Register function, allowing the user to register their name that stays consistent throughout the game prior to play again, which then resets
void Game::Register()
{
	string inputname;

	cout << "What is your name? ";

	cin >> inputname;

	p->Playername = inputname;

	cout << "" << endl;
	cout << "Welcome " << p->Playername << "!!!" << endl;

	getline(cin, inputname);
}

//the function that holds the game logic
void Game::LocationFunct(const string& f)
{
	string line;
	ifstream ifs(f);

	if (!ifs.is_open())
	{
		exit(0);
	}

	bool valid = true;
	while (getline(ifs, line))
	{
		line = Cut(line);

		if (line.size() == 0)
		{
			continue;
		}

		vector<string> parts = Split(line, ':');

		if (parts.size() != 2)
		{
			valid = false;
			break;
		}

		string type = parts[0];
		string name = parts[1];

		if (type == "Item")
		{
			getline(ifs, line);
			parts = Split(line, ':');
			string description = parts[1];

			getline(ifs, line);
			parts = Split(line, ':');

			if (parts.size() == 0)
			{
				Item* item = new Item(name, description);
				items[item->getName()] = item;
				itemNames.push_back(item->getName());
			}

			else
			{
				Container* container = new Container(name, description);
				vector<string> contents = Split(parts[1], ',');
				for (size_t i = 0; i < contents.size(); i++)
				{
					container->addItem(contents[i]);
					itemNames.push_back(contents[i]);
				}

				getline(ifs, line);
				parts = Split(line, ':');

				if (parts.size() > 0)
				{
					vector<string> keys = Split(parts[1], ',');

					for (size_t i = 0; i < keys.size(); i++)
					{
						container->addKey(keys[i]);
						itemNames.push_back(keys[i]);
					}

					getline(ifs, line);
				}

				items[container->getName()] = container;
				itemNames.push_back(container->getName());
			}
		}

		else if (type == "Location")
		{
			int number = atoi(name.c_str());

			getline(ifs, line);
			parts = Split(line, ':');
			name = parts[1];

			getline(ifs, line);
			parts = Split(line, ':');
			string description = parts[1];

			Location* location = new Location(number, name, description);

			getline(ifs, line);
			parts = Split(line, ':');
			vector<string> contents = Split(parts[1], ',');
			for (size_t i = 0; i < contents.size(); i++)
			{

				if (items.find(contents[i]) != items.end())
				{
					location->addItem(items[contents[i]]);
				}

				else
				{
					delete location;
					valid = false;
					break;
				}
			}

			while (getline(ifs, line))
			{
				line = Cut(line);

				if (line.size() == 0)
				{
					break;
				}

				parts = Split(line, ',');
				contents = Split(parts[0], ' ');

				string direction = contents[0];
				int nextLocationNumber = atoi(contents[1].c_str());
				string key = "";

				if (parts.size() > 1)
				{
					key = parts[1];
				}

				location->Connection(toLower(direction), nextLocationNumber, key);

				if (key != "") {
					itemNames.push_back(key);
				}

				locationNumbers.push_back(nextLocationNumber);
			}

			locations[location->getNumber()] = location;
			locationNumbers.push_back(location->getNumber());
		}

		else
		{
			valid = false;
			break;
		}
	}

	if (!valid)
	{
		exit(0);
	}
}

//the play function where all the input and results get handled and processed
void Game::Play()
{
	//prints the content in welcome text function
	WelcomeText();

	//prints the content in Register function
	Register();

	//prints the content in Print function within player class
	p->Print();

	// array full of acceptable commands
	string inputoptions[9] =
	{
		"north", // 0
		"south", // 1
		"east", // 2
		"west", // 3
		"look", // 4
		"quit", // 5
		"take", // 6
		"drop", // 7
		"open", // 8
	};

	cout << "" << endl;
	cout << "What is your next move? ";

	cout << "> ";
	string Input;

	//loop which constantly askes the user for a input
	while (getline(cin, Input))
	{
		string action;
		string target;

		Parsedata(Input, action, target);

		//if statement checking whether or not the action input was a movement input
		if (action == inputoptions[0] || action == inputoptions[1] || action == inputoptions[2] || action == inputoptions[3])
		{
			p->Move(action);

			p->steps = p->steps + 1;
		}

		//if statement checking whether or not the action input was a look input
		if (action == inputoptions[4])
		{
			p->Print();
		}

		//if statement checking whether or not the action input was a quit input
		if (action == inputoptions[5])
		{
			cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
			cout << "I'm sad to hear, " << p->Playername << " you have decided to leave the game!" << endl;
			cout << "" << endl;
			cout << "You had a good run! " << endl;
			cout << "" << endl;
			cout << "Made by Nathaniel! " << endl;
			cout << "----------------------------------------------------------------------------------------------------------------------" << endl;

			break;
		}
		
		//if statement checking whether or not the action input was a item type input
		if (action == inputoptions[6] || action == inputoptions[7] || action == inputoptions[8])
		{
			if (target != "")
			{
				p->steps = p->steps + 1;

				target = toLower(target);

				if (action == inputoptions[6])
				{
					cout << "" << endl;
					p->takeItem(target);
				}

				if (action == inputoptions[7])
				{
					cout << "" << endl;
					p->dropItem(target);
				}

				if (action == inputoptions[8])
				{
					cout << "" << endl;
					p->openItem(target);
				}
			}	

			//if statement checking that the target input is not null for an item type input
			if (target == "")
			{
				cout << "" << endl;
				cout << "Please input something to " << action << "!" << endl;
			}
		}

		//if statement checking that the correct input is being inputted
		if (!(action == inputoptions[0]))
		{
			if (!(action == inputoptions[1]))
			{
				if (!(action == inputoptions[2]))
				{
					if (!(action == inputoptions[3]))
					{
						if (!(action == inputoptions[4]))
						{
							if (!(action == inputoptions[5]))
							{
								if (!(action == inputoptions[6]))
								{
									if (!(action == inputoptions[7]))
									{
										if (!(action == inputoptions[8]))
										{
											{
												cout << "This command is not recognised!" << endl;

												Controls();
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}

		//if statement checking whether or not the user has won the game
		if (p->Won())
		{
			cout << "" << endl;
			cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
			cout << "Congratulations, " << p->Playername << " you have finished the game, and arrived at the final destination!!!" << endl;
			cout << "" << endl;
			cout << "You have finished in " << p->steps << " move/s!" << endl;
			cout << "" << endl;
			cout << "Thanks for playing! " << endl;
			cout << "" << endl;
			cout << "Made by Nathaniel! " << endl;
			cout << "----------------------------------------------------------------------------------------------------------------------" << endl;

			//calls play again function to ask the user if they'll like to play again
			PlayAgain();

			break;
		}

		//constant print that checks the players step count
		cout << "" << endl;
		cout << "You have taken " << p->steps << " move/s!" << endl;
		cout << "" << endl;

		cout << "" << endl;
		cout << "What is your next move? ";
		cout << "> ";
	}
}

//this is used to split parts of the datafile so the program can understand data once called
vector<string> Game::Split(string s, char c)
{
	vector<string> tokens;

	string token;
	istringstream iss(s);
	while (getline(iss, token, c))
	{
		token = Cut(token);

		if (token.size() > 0)
		{
			tokens.push_back(token);
		}
	}

	return tokens;
}

//used to change the input into lower case letters so the program can understand the input
string Game::toLower(string s) 
{
	string result = "";
	for (size_t i = 0; i < s.size(); i++) 
	{
		char ch = s[i];

		if (ch >= 'A' && ch <= 'Z') 
		{
			ch += 'a' - 'A';
		}
		result += ch;
	}
	return result;
}

//used to get rid of the spaces so the program can understand
string Game::Cut(string s)
{
	if (s.size() == 0)
	{
		return s;
	}

	int start = -1;
	int end = -1;

	for (int i = 0; i < (int)s.size(); i++)
	{
		char ch = s[i];
		if (!isspace(ch))
		{
			start = i;
			break;
		}
	}

	for (int i = (int)s.size() - 1; i >= 0; i--)
	{
		char ch = s[i];

		if (!isspace(ch)) {
			end = i;
			break;
		}
	}

	if (start == -1)
	{
		return "";
	}

	return s.substr(start, end - start + 1);
}

// Parses the game data.
void Game::Parsedata(string i, string &a, string &t)
{
	a = t = "";
	i = Cut(i);

	istringstream iss(i);
	iss >> a;

	a = toLower(a);
	t = Cut(i.substr(a.size(), i.size() - a.size()));
}

Game::~Game()
{
	delete p;

	map<string, Item*>::iterator it1 = items.begin();
	while (it1 != items.end())
	{
		delete it1->second;
		it1++;
	}

	map<int, Location*>::iterator it2 = locations.begin();
	while (it2 != locations.end())
	{
		delete it2->second;
		it2++;
	}
}
