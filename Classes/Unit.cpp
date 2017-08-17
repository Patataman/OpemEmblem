#include "Unit.h"

Unit::Unit()
{
    Unit::unit = nullptr;
    Unit::hp = 0;
    Unit::atk = 0;
    Unit::movement = 3;
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
    log("wait");
    changeShader(1);
}

void Unit::ready()
{
    Unit::state = true;
    changeShader(0);
}

bool Unit::attack(Unit* enemy)
{
    return false;
}

void Unit::changeShader(short int code)
{
    /**
    - 0: Original shader
    - 1: Gray shader
    - 2: Blue shader
    - 3: Red shader
    **/

    log("changeShader");

    auto gl_cache = GLProgramCache::getInstance();

    if (gl_cache->getGLProgram("originalColorShader") == nullptr)
    {
        gl_cache->addGLProgram(Unit::unit->getGLProgram(), "originalColorShader");
    }

    GLProgram* p = nullptr;
    switch(code) {
        //gray shader
        case 1: {
                    log("code 1");
                    p = gl_cache->getGLProgram("grayShader");
                    if (p == nullptr)
                    {
                        p = new GLProgram();
                        p->initWithFilenames("shaders/gray.vsh", "shaders/gray.fsh");
                        p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
                        p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
                        p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);
                        p->link();
                        p->updateUniforms();
                        gl_cache->addGLProgram(p, "grayShader");
                    }
                    break;
                }
        //blue shader
        case 2: {
                    log("code 2");
                    p = gl_cache->getGLProgram("blueShader");
                    if (p == nullptr)
                    {
                        p = new GLProgram();
                        p->initWithFilenames("shaders/blue.vsh", "shaders/blue.fsh");
                        p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
                        p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
                        p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);
                        p->link();
                        p->updateUniforms();
                        gl_cache->addGLProgram(p, "blueShader");
                    }
                    break;
                }
        //red shader
        case 3: {
                    log("code 3");
                    p = gl_cache->getGLProgram("redShader");
                    if (p == nullptr)
                    {
                        p = new GLProgram();
                        p->initWithFilenames("shaders/red.vsh", "shaders/red.fsh");
                        p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
                        p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
                        p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);
                        p->link();
                        p->updateUniforms();
                        gl_cache->addGLProgram(p, "redShader");
                    }
                    break;
                }
        //original shader (0)
        default: {
                    log("default");
                    if (gl_cache->getGLProgram("originalColorShader") != nullptr)
                    {
                        p = gl_cache->getGLProgram("originalColorShader");
                    }
                }
    }
    auto programState = GLProgramState::create(p);
    Unit::unit->setGLProgramState(programState);
}