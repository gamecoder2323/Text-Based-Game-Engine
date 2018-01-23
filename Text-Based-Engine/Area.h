#pragma once
#include <vector>
#include "Inventory.h"
#include "Interactables.h"

enum class Action { GRAB, GO, LIGHT, TOSS, NONE }; // light is for stuff like 'light' a torch

class Area
{
public:
	Area();
	std::string name;
	void description(std::string describe, int x, int y);
	std::string areaDescription;
	//std::string buffer;
	void giveInteractions(Interactables interactable);
	std::vector<Interactables> interactables;
	std::string Area::getHint();
	std::string generalDescription;
private:
	


};

//Give areas position and objects and/or interactions