#include "Item.h"

Item::Item()
{

}

Item::~Item()
{

}

Item::Item(std::string name, short int dmg, short int hit, short int range)
{
	Item::name = name;
	Item::damage = dmg;
	Item::hit = hit;
	Item::range = range;
}