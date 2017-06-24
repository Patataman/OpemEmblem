#ifndef __BATTLE_SCENE_H__
#define __BATTLE_SCENE_H__

#include "cocos2d.h"
#include "Unit.h"

class BattleScene : public cocos2d::Scene
{
public:

    std::vector<Unit> allies, enemies;

    static cocos2d::Scene* createScene();
    virtual bool init();
    
    //// a selector callback
    void drawGrid();
    void actionMenu(Unit* unit);
    void loadAllyUnits(cocos2d::TMXLayer* tileMap);
    //void changeToBattle(cocos2d::Ref* pSender);
    //void changToOptions(cocos2d::Ref* pSender);
    //
    // implement the "static create()" method manually
    CREATE_FUNC(BattleScene);
};

#endif // __BATTLE_SCENE_H__
