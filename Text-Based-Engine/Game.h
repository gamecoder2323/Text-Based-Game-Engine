#pragma once
#include <vector>
#include "Inventory.h"
#include "Area.h"

class Game
{
public:
	Game();
	void start();

private:
	void initInventory();
	std::vector<Inventory> allItems;
	Inventory inventory[16];
	int itemSlotIterator;
	void print(std::string string);
	void confirm();
	std::string name;
	void initAreas();
	void recognize(std::string input);
	void mainGame();
	int x;
	int y;
	void eventCheck(std::string verb, std::string noun);
	void grab(std::string noun);
	Action checkAction(std::string verb);
	void initInteractables();
	void areaSetUp(int posX, int posY, std::string name, std::string areaDesc);
	Area map[10][10];
	std::vector<Interactables> allInteracts;
	Area currentArea;
	void go(std::string noun);
};

