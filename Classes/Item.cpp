#include "Item.h"

Item::Item()
{

}

Item::~Item()
{

}

Item::Item(std::string name, short int dmg, short int hit)
{
	Item::name = name;
	Item::damage = dmg;
	Item::hit = hit;
}