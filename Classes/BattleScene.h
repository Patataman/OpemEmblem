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
    bool onMenu, turn;

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
    //keyboard events on key pressed
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    //Unit's action menu
    void actionMenu(Unit* unit, Unit* enemy);
    //Cell selector actions (move and select units)
    void cellSelector(EventKeyboard::KeyCode keyCode);
    //--------------------//
    //keyboard events on key released
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
    // implement the "static create()" method manually
    CREATE_FUNC(BattleScene);
};

#endif // __BATTLE_SCENE_H__
