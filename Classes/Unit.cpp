#include "Unit.h"

//Unit* Unit::create(std::filename)
//{
//    Unit* pSprite = new Unit();
//
//    if (pSprite->initWithSpriteFrameName(filename))
//    {
//        pSprite->autorelease();
//        pSprite->initOptions();
//        pSprite->addEvents();
//
//        return pSprite;
//    }
//
//    CC_SAFE_DELETE(pSprite);
//    return NULL;
//}

void Unit::setAttr(short int hp, short int atk, short int movement, Vec2 pos, Item weapon)
{
	Unit::hp = hp;
	Unit::atk = atk;
	Unit::movement = movement;
	Unit::position = pos;
	Unit::weapon = weapon;
}

void Unit::move(Vec2 dest)
{
	Unit::position = dest;
}

void Unit::wait()
{
	Unit::state = false;
}

void Unit::ready()
{
	Unit::state = true;
}

bool Unit::attack(Unit* enemy)
{
	return false;
}