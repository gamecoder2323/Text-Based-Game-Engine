#pragma once
#include <vector>

enum class Property { NONE, WOOD, METAL, SHARP, HEAVY, FLAMMABLE, EXPLOSIVE, UNLOCK, GRAB, HARD };
//really, "Item" class


class Inventory {
public:
	
	Inventory();
	std::string name;
	Inventory(std::string objName, Property propOne);
	Inventory(std::string objName, Property propOne, Property propTwo);
	Inventory(std::string objName, Property propOne, Property propTwo, Property propThree);

	void setProperty(Property prop);
	bool searchProperty(Property search);

private:
	std::vector<Property> itemProperty;
};

//possibly add properties to items, making it easier for an event to happen if an item has certain properties, like:
//A key has properties: {OPEN, METAL, HEAVY, SMALL}. This means that it can be used to unlock a door/chest, conduct electricity,
//hold stuff down/knock enemies out, or fit somewhere small, respectively.