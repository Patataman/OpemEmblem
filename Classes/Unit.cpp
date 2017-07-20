#include "Unit.h"

Unit::Unit()
{
    Unit::unit = nullptr;
    Unit::hp = 0;
    Unit::atk = 0;
    Unit::movement = 0;
    Unit::state = true;
    Unit::position.set(Vec2(0,0));
    Unit::weapon = nullptr;
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
    auto gl_cache = GLProgramCache::getInstance();

    if (gl_cache->getGLProgram("originalColorShader") == nullptr)
    {
        gl_cache->addGLProgram(Unit::unit->getGLProgram(), "originalColorShader");
    }

    auto p = gl_cache->getGLProgram("grayscaleShader");
    if (p == nullptr)
    {
        p = new GLProgram();
        p->initWithFilenames("gray.vsh", "gray.fsh");
        p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
        p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
        p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);
        p->link();
        p->updateUniforms();
        gl_cache->addGLProgram(p, "grayscaleShader");
    }
    auto programState = GLProgramState::create(p);
    Unit::unit->setGLProgramState(programState);
}

void Unit::ready()
{
    Unit::state = true;

    auto gl_cache = GLProgramCache::getInstance();
    if (gl_cache->getGLProgram("originalColorShader") != nullptr)
    {
        auto p = gl_cache->getGLProgram("originalColorShader");
        auto programState = GLProgramState::create(p);
        Unit::unit->setGLProgramState(programState);
    }
}

bool Unit::attack(Unit* enemy)
{
    return false;
}