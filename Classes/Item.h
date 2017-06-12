#ifndef __ITEM_H__
#define __ITEM_H__

#include "cocos2d.h"
#include "iostream"

USING_NS_CC;

class Item
{
public:

	std::string name;
	short int damage, hit;

	Item(std::string name, short int dmg, short int hit);
};

#endif // __ITEM_H__