#include "BattleScene.h"
#include "Unit.h"
#include "SimpleAudioEngine.h"
#include <iostream>

USING_NS_CC;

//windows size
auto visibleSize = Director::getInstance()->getVisibleSize();
Vec2 origin = Director::getInstance()->getVisibleOrigin();

Scene* BattleScene::createScene()
{
    return BattleScene::create();
}

// main scene
bool BattleScene::init()
{
    //super init
    if ( !Scene::init() )
    {
        return false;
    }

    //load the tile map
    auto tileMap = TMXTiledMap::create("TileMaps/test.tmx");
    //auto walkable_layer = tileMap->getLayer("walkable");

    //scale x4
    tileMap->setScale(4);
    // draws the tile map
    addChild(tileMap, 0, 0);
    //draws the cells on the map
    this->drawGrill();

    auto prueba = Unit::create("sprites/test.png");
    prueba->setPosition(0,0);
    addChild(prueba, 0, 1);

    //Text label for debugging
    auto label = Label::createWithTTF("Battle 0.1a", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    //draw the text
    addChild(label, 1);

    return true;
}

/**
    Draw the cells of the map.
    Cell dimension is 16*16 pixels with x4 scaled.
**/
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

/**
    Unit's action menu.
    Can move, attack (if enemy units at range) and wait.
**/
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
                                          CC_CALLBACK_0(Unit::wait, unit) );
    unitMenu.pushBack(moveItem);
    unitMenu.pushBack(attackItem);
    //unitMenu.pushBack(bagItem);
    unitMenu.pushBack(waitItem);

    // create menu, it's an autorelease object
    auto menu = Menu::createWithArray(unitMenu);
    menu->setPosition(Vec2(visibleSize.width - menu->getContentSize().width/2,
                      visibleSize.height - menu->getContentSize().height/2));
    this->addChild(menu, 1);
}