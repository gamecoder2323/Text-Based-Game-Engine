#include "stdafx.h"
#include "Inventory.h"
#include <string>

Inventory::Inventory() {

}


Inventory::Inventory(std::string objName, Property propOne) {
	name = objName;
	itemProperty.push_back(propOne);
}

Inventory::Inventory(std::string objName, Property propOne, Property propTwo) {
	name = objName;
	itemProperty.push_back(propOne);
	itemProperty.push_back(propTwo);
}

Inventory::Inventory(std::string objName, Property propOne, Property propTwo, Property propThree) {
	name = objName;
	itemProperty.push_back(propOne);
	itemProperty.push_back(propTwo);
	itemProperty.push_back(propThree);
}

void Inventory::setProperty(Property prop) {
	itemProperty.push_back(prop);
}

bool Inventory::searchProperty(Property search) {
	for (int i = 0; i < sizeof(itemProperty); i++) {
		if (itemProperty[i] == search) {
			return true;
		} else {
			return false;
		}
	}
}