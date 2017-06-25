#include "Unit.h"

Unit::Unit()
{
	Unit::unit = NULL;
	Unit::hp = 0;
	Unit::atk = 0;
	Unit::movement = 0;
	Unit::state = true;
	Unit::position = Vec2(0,0);
	Unit::weapon = NULL;
}

Unit::Unit(short int hp, short int atk, short int movement, Vec2 pos, Item* weapon)
{
	Unit::hp = hp;
	Unit::atk = atk;
	Unit::movement = movement;
	Unit::position = pos;
	Unit::weapon = weapon;
	Unit::state = true;
}

Unit::~Unit(){
	delete Unit::unit;
	delete Unit::weapon;
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