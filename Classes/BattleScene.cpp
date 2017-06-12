#include "BattleScene.h"
#include "SimpleAudioEngine.h"
#include "Unit.h"
#include <iostream>

USING_NS_CC;

Scene* BattleScene::createScene()
{
    return BattleScene::create();
}

// on "init" you need to initialize your instance
bool BattleScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    // create a TMX map
    auto tileMap = TMXTiledMap::create("TileMaps/test.tmx");
    //auto walkable_layer = tileMap->getLayer("walkable");

    tileMap->setScale(4);
    addChild(tileMap, 0, 0);

    this->drawGrill();

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto prueba = Unit::create("sprites/test.png");
    prueba->setPosition(0,0);
    addChild(prueba, 0, 1);

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Battle 0.1a", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    addChild(label, 1);

    return true;
}

void BattleScene::drawGrill()
{
    Color4F color(0, 0, 0.5, 0.5);
    auto draw_node = DrawNode::create();
    short int x, y;
    for (short int i = 0; i < 8 + 1; i++)
    {
        x = i * 16*4;
        draw_node->drawLine(Vec2(x, 0), Vec2(x, 500), color);
    }
    for (short int i = 0; i < 5 + 1; i++)
    {
        y = i * 16*4;
        draw_node->drawLine(Vec2(0, y), Vec2(500, y), color);
    }
    addChild(draw_node, 1); 
}

void BattleScene::actionMenu(Unit* unit)
{
    Vector<MenuItem*> unitMenu;
    auto moveItem = MenuItemFont::create("Move",
                                          NULL);
    auto attackItem = MenuItemFont::create("Attack",
                                          NULL);
    //auto bagItem = MenuItemFont::create("Bag",
    //                                      NULL);
    auto waitItem = MenuItemFont::create("Wait",
                                          unit->changeState(false));
    unitMenu.pushBack(moveItem);
    unitMenu.pushBack(attackItem);
    unitMenu.pushBack(bagItem);
    unitMenu.pushBack(waitItem);

    // create menu, it's an autorelease object
    auto menu = Menu::createWithArray(unitMenu);
    menu->setPosition(Vec2(visibleSize.width - menu->getContentSize().width/2,
                      visibleSize.height - menu->getContentSize().height/2));
    this->addChild(menu, 1);
}