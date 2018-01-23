#pragma once
#include <string>
#include "Inventory.h"



class Interactables
{
public:
	Interactables();
	std::string nameOfObj;
	Property interactMatch;

	std::string giveHint(std::string hintToUse);
	bool isTriggered;
	std::string hint;
	void init(std::string name, Property match);
private:

};

