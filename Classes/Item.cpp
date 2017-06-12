#include "Item.h"

Item::Item(std::string name, short int dmg, short int hit)
{
	Item::name = name;
	Item::dmg = dmg;
	Item::hit = hit;
}