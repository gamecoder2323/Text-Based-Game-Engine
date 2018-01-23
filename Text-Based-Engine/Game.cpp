#include "stdafx.h"
#include "Game.h"
#include "Inventory.h"
#include <iostream>
#include "Interactables.h"


//Note to self: 'Sub Areas' as they will be called, will be regular areas made in a different array than 'maps' that will be a 1-D array.


//INSTRUCTIONS: IF YOU ARE GOING TO USE THIS AARON, PLEASE READ! THIS IS A REFERENCE GUIDE.
//
//To create a new Area, first you give a new interactable to an area. You go to initAreas to do this, then you give the item a hint. From there, you create an areaSetup.
//In the areaSetup, you specify the (x, y) coordinates and give it a name, and a description of it when there aren't any interacts there.
//After that, you're done with creating an area.
//
//
//That is, unless you wanted to create a new interactable for the area. Now, to do this, you go to initInteractables, and then type Interactables followed by a space,
//and then the name of your interactable. In the initialization list, you type:
//
//name.init("name", Property::*whatever the name of the property that you want to trigger it is*);
//
//
//If you wish to make a new item, follow the same steps as you would an interactable, except every time you see 'interactable' replace it with 'Inventory' (Names included)
//
//
//To create a new property, click on Area.h and make a new name for it. Be sure to capitalize the property though!
//
//
//I have placed all the tools you will need to use near the top. This is the basic engine. All that I'll be doing now is expanding it, and adding new features.
//Add any recommendations at the bottom of this program, in a comment. :)




Game::Game()
{
	x = 5;
	y = 5;
	initInteractables();
	initInventory();
	initAreas();
	itemSlotIterator = 0;
}





//Start of Game setup




void Game::initAreas() {

	//initialization list for map interacts.
	map[5][5].giveInteractions(allInteracts[2]); // The 'allInteracts' here is a list of interactables that I put in a certain order. The order is in initInteractables.
	map[5][5].interactables[0].giveHint("It seems there is an old sword lying in the ground."); // This is what appears if you haven't interacted with something in an area.
	map[5][4].giveInteractions(allInteracts[4]);
	map[5][4].interactables[0].giveHint("There are stones in the wall that appear to be loose.");
	map[6][5].giveInteractions(allInteracts[0]);
	map[6][6].giveInteractions(allInteracts[1]);
	map[6][6].interactables[0].giveHint("In front of the tower, there is an old door.");
	map[4][5].giveInteractions(allInteracts[0]);





	//Basic Setup: Do this first.

	areaSetUp(5, 5, "Mountains 1", "You are standing on a tall mountain. It is very snowy here. You look around. You appear to be on a large island. You can see miles of shoreline at the edges of the island. ");
	areaSetUp(5, 4, "Mountain Ravine", "You walk through a narrow ravine in the mountains. Erosion has worn down the stones of an unknown civilization. To the south, there appears to be a bridge. ");
	areaSetUp(6, 5, "Mountains 2", "You cross into rocky terrain. The mountain range stretches far to the east. To the north of you appears to be a weathered stone tower. It looks like it could reveal some clues about this island. ");
	areaSetUp(6, 6, "Stone Tower", "You have come across an ancient tower. It's stone bricks look weathered from hundreds of years of erosion. It looks very unstable. You see a wooden door in the side of the structure. ");
	areaSetUp(4, 5, "Grasslands 1", "You have come to the boundary of the Grasslands. It is very flat and has a cool breeze that comes from the North. From here, you can see mountains to the East.");



}


void Game::initInteractables() {
	//Interactables to be used
	Interactables none;
	Interactables openable;
	Interactables sword;
	Interactables explodable;
	Interactables stone;

	//Initialize the properties of interactables
	none.init("none", Property::NONE);
	openable.init("door", Property::UNLOCK);
	sword.init("sword", Property::GRAB);
	explodable.init("gunpowder", Property::FLAMMABLE);
	stone.init("stone", Property::HARD);

	//
	allInteracts.push_back(none); //0
	allInteracts.push_back(openable); //1
	allInteracts.push_back(sword); //2
	allInteracts.push_back(explodable); //3
	allInteracts.push_back(stone); //4
	
	//Add new interacts above this line: put them at the bottom!
}

void Game::initInventory() {
	//init all game Items
	Inventory key("key", Property::UNLOCK, Property::METAL);
	Inventory sword("sword", Property::SHARP, Property::METAL);
	Inventory torch("torch", Property::WOOD, Property::FLAMMABLE);
	Inventory stone("stone", Property::HARD, Property::HEAVY);

	//Add them to the list of items in the game
	allItems.push_back(key);
	allItems.push_back(sword);
	allItems.push_back(torch);
	allItems.push_back(stone);
}





//End of Game setup





//Start of Engine

void Game::mainGame() {
	std::string areaHint;
	while (true) {

		currentArea = map[x][y];
		areaHint = currentArea.getHint();
		currentArea.areaDescription = currentArea.generalDescription + areaHint;
		print(currentArea.areaDescription);
		std::string in;
		std::getline(std::cin, in);
		recognize(in);
		//print (std::to_string(map[5][5].interactables[0].isTriggered));
	}
}


void Game::start() {
	initAreas();
	print("\n\n\n\n\n\n\n\n                             WELCOME TO ARONTANIA\n\n\n\n             Type in 2-word commands, in the form of VERB-NOUN.\n\n\n\n\n\n\n\n");
	confirm();
	print("What is your name?");
	std::getline(std::cin, name);

	print("Hello " + name + "!");
	confirm();
	mainGame();
}

void Game::print(std::string string) {
	std::cout <<std::endl << string << std::endl;
}

void Game::confirm() {
	std::cin.ignore();
	//system("cls");
}


void Game::recognize(std::string input) {
	int space = input.find(" ");
	//int nounLength = input.length() - space;
	std::string verb = input.substr(0, space);
	std::string noun = input.substr(space + 1, input.length() - space);
	eventCheck(verb, noun);
}

void Game::areaSetUp(int posX, int posY, std::string name, std::string areaDesc) {

	//basic area set up
	map[posX][posY].name = name;
	map[posX][posY].description(areaDesc, posX, posY);
}



void Game::eventCheck(std::string verb, std::string noun) {
	Action action;
	action = checkAction(verb);
	switch (action) {
		case Action::GO:
			go(noun);
			break;
		case Action::GRAB:
			grab(noun);
			break;
		
		case Action::NONE:
			print("You can't " + verb + ".");
			break;
		default:
			print("Something went wrong!");
			break;
	}

	return;
}

void Game::grab(std::string noun) {
	//return the inventory item for an interact.
	for (int i = 0; i < sizeof(currentArea.interactables); ++i) {

		for (int j = 0; j < sizeof(allItems); ++j) {
			if (currentArea.interactables[i].nameOfObj == noun) {
				if (itemSlotIterator > 15) {
					print("You can't hold anymore items! Type 'toss' and then the item you would like to discard to remove an item.");
					return;
				}
				else if (allItems[j].name == currentArea.interactables[i].nameOfObj) {
					if (map[x][y].interactables[i].isTriggered == 0) {
						inventory[itemSlotIterator] = allItems[j];
						print("You grabbed the " + inventory[itemSlotIterator].name + "!");
						itemSlotIterator++;
						map[x][y].interactables[i].isTriggered = true;
						return;
					}
					else {
						print("You can't grab that.");
						return;
					}
				}
		}
			
		else {
			print("You can't grab a " + noun + " here.");
			return;
			}
		}
	}
}

Action Game::checkAction(std::string verb) {
	//synonyms
	if (verb == "grab" || verb == "take") {
		return Action::GRAB;
	}
	else if (verb == "go" || verb == "leave" || verb == "travel" || verb == "walk" || verb == "hike" || verb == "trek") {
		return Action::GO;
	}
	else if (verb == "toss" || verb == "remove" || verb == "discard" || verb == "trash") {
		return Action::TOSS;
	}
	else {
		return Action::NONE;
	}

}


void Game::go(std::string noun) {
	if (noun == "north" || noun == "n") {
		++y;
	}
	else if (noun == "south" || noun == "s") {
		--y; 
	
	}
	else if (noun == "east" || noun == "e") {
		++x;
	}
	else if (noun == "west" || noun == "w") {
		--x; 
	}
	else {
		print("You can't go " + noun + "!");
	}
}



//End of Engine