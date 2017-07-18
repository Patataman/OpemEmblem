#include "MainScene.h"
#include "BattleScene.h"
#include "OptionScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* MainScene::createScene()
{
    return MainScene::create();
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    Vector<MenuItem*> menuItems;
    auto battleItem = MenuItemFont::create("Battle",
    										CC_CALLBACK_1(MainScene::changeToBattle, this));
    auto optionItem = MenuItemFont::create("Options",
    										CC_CALLBACK_1(MainScene::changeToOptions, this));
    auto closeItem = MenuItemFont::create("Quit",
    										CC_CALLBACK_1(MainScene::quitGame, this));
    menuItems.pushBack(battleItem);
    menuItems.pushBack(optionItem);
    menuItems.pushBack(closeItem);

    // create menu, it's an autorelease object
    auto menu = Menu::createWithArray(menuItems);
    //menu->setPosition(Vec2(visibleSize.width - menu->getContentSize().width/2,
    //                    menu->getContentSize().height/2));
    menu->alignItemsInRows(3);
    menu->alignItemsVertically();

    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Free Emblem 0.1a", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    return true;
}

void MainScene::changeToBattle(Ref* pSender)
{
    // change scene
    auto battleScene = BattleScene::createScene();
    Director::getInstance()->pushScene(battleScene);
}

void MainScene::changeToOptions(Ref* pSender)
{
	// change scene
    auto optionScene = OptionScene::createScene();
    Director::getInstance()->pushScene(optionScene);	
}

void MainScene::quitGame(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    	exit(0);
	#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}
