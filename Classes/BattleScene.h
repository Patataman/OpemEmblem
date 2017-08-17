#ifndef __BATTLE_SCENE_H__
#define __BATTLE_SCENE_H__

#include "cocos2d.h"
#include "Unit.h"

class BattleScene : public cocos2d::Scene
{
public:

    std::vector<Unit*> allies, enemies;
    Unit selector;
    TMXTiledMap* tileMap;
    std::vector<Unit*> map;
    bool turn;
    /*
    0: Game interation
    1: On menu
    2: Moving unit
    3: Attack state
    */
    short int state, rectsDrew;

    static cocos2d::Scene* createScene();
    virtual bool init();
    
    //generate the map
    void generateMap();
    //draws the line to define cells
    void drawGrid();
    //Change to the other player
    void changeTurn();
    //draws and create ally units
    void loadAllyUnits();
    //draws and create enemy units
    void loadEnemyUnits();
    //create and add all the keyboard events
    void addKeyboardEvents();
    //Unit's action menu
    void actionMenu(Unit* unit, bool enemy);
    //Cell selector actions (move and select units)
    void cellSelector(EventKeyboard::KeyCode keyCode);
    //Move unit action
    void moveUnit(Unit* unit);
    //Attack unit action
    void attackUnit(Unit* unit);
    //--------------------//
    //keyboard events on key pressed
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    //keyboard events on key released
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
    //mouse down events
    //void onMouseDown(Event* event);
    //mouse up events
    void onMouseUp();
    // implement the "static create()" method manually
    CREATE_FUNC(BattleScene);
};

#endif // __BATTLE_SCENE_H__
