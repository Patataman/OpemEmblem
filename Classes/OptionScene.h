#ifndef __OPTION_SCENE_H__
#define __OPTION_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class OptionScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    //// a selector callback
    virtual void backToMenu();
    //void changeToBattle(cocos2d::Ref* pSender);
    //void changToOptions(cocos2d::Ref* pSender);
    //
    // implement the "static create()" method manually
    CREATE_FUNC(OptionScene);
};

#endif // __OPTION_SCENE_H__
