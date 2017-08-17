#ifndef __ITEM_H__
#define __ITEM_H__

#include "cocos2d.h"
#include "iostream"

USING_NS_CC;

class Item
{
public:

	Item();
	Item(std::string name, short int dmg, short int hit, short int range);
	~Item();
	
	std::string name;
	short int damage, hit, range;

};

#endif // __ITEM_H__