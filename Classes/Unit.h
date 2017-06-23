#ifndef __UNIT_H__
#define __UNIT_H__

#include "cocos2d.h"
#include "Item.h"

USING_NS_CC;

class Unit
{
public:

    cocos2d::Sprite* unit;
	short int hp, atk, movement;
	bool state;        //available (true) unavailable (false)
	Vec2 position;
	Item weapon;

    //static Unit* create(std::string filename);
    Unit();
    ~Unit();
    virtual void setAttr(short int hp, short int atk, short int movement, Vec2 pos, Item weapon);
    virtual void move(Vec2 dest);
    virtual void wait();
    virtual void ready();
    virtual bool attack(Unit* enemy);
    //virtual void 
    //bool idkwhatelse();
};

#endif // __UNIT_H__