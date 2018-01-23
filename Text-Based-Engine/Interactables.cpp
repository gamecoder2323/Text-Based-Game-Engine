#include "stdafx.h"
#include "Interactables.h"



Interactables::Interactables()
{
	isTriggered = 0;
}


std::string Interactables::giveHint(std::string hintToUse) {
	if (!isTriggered) {
		hint = hintToUse;
		return hint;
	}
	else {
		hint = "";
		return hint;
	}
}

void Interactables::init(std::string name, Property match) {
	nameOfObj = name;
	interactMatch = match;
}