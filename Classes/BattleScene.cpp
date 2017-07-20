#include "BattleScene.h"
#include "Unit.h"
#include "SimpleAudioEngine.h"
#include <iostream>

USING_NS_CC;

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

    this->onMenu = false;
    this->turn = true;

    //load the tile map
    this->tileMap = TMXTiledMap::create("TileMaps/test.tmx");
    //scale x4
    this->tileMap->setScale(4);
    this->generateMap();
    // draws the tile map
    addChild(tileMap, -1);

    //draws the cells on the map
    this->drawGrid();

    auto spritePlist = SpriteFrameCache::getInstance();
    spritePlist->addSpriteFramesWithFile("sprite/test.plist");

    //load ally units
    this->loadAllyUnits();
    //load enemy units
    this->loadEnemyUnits();

    this->selector.unit = Sprite::create("sprite/selector.png");
    this->selector.unit->setScale(4);
    this->selector.position.set(this->allies[0]->position);
    this->selector.unit->setPosition((this->map[this->allies[0]->position.y*
                                                this->tileMap->getMapSize().width +
                                                this->allies[0]->position.x]->position + 
                                        Vec2(8,8))*4);
    addChild(this->selector.unit,1);

    //Follow::create(object to follow, map dimensions)
    auto follow = Follow::create(this->selector.unit,
                                Rect(0,
                                     0, 
                                     this->tileMap->getMapSize().width*this->tileMap->getTileSize().width*4,
                                     this->tileMap->getMapSize().height*this->tileMap->getTileSize().height*4));
    this->runAction(follow);


    this->addKeyboardEvents();

    return true;
}

void BattleScene::generateMap()
{
    int max_x = this->tileMap->getMapSize().width;
    int max_y = this->tileMap->getMapSize().height;
    this->map.resize(max_x*max_y);

    for(int x = 0; x< max_x; x++)
    {
        for(int y = 0; y< max_y; y++)
        {
            //i*m + j -> row * num_columns + column
            //Needs to save the position because the Sprite 
            //returned by getTileAt doesn't have a position value
            this->map[y*max_x + x] = new Unit;
            this->map[y*max_x + x]->unit = this->tileMap->getLayer("all")->getTileAt(Vec2(x, y));
            this->map[y*max_x + x]->position = Vec2((int)this->tileMap->getLayer("all")->getPositionAt(Vec2(x, y)).x,
                                                    (int)this->tileMap->getLayer("all")->getPositionAt(Vec2(x, y)).y);
        }
    }
}

/**
    Draw the cells of the map.
    Cell dimension is 16*16 pixels with x4 scaled.
**/
void BattleScene::drawGrid()
{
    Color4F color(0, 0, 0.5, 0.5);
    auto draw_node = DrawNode::create();
    short int x, y;
    for (short int i = 0; i < 8 + 1; i++)
    {
        x = i * 16*4;
        draw_node->drawLine(Vec2(x, 0),
                            Vec2(x, this->tileMap->getMapSize().height*this->tileMap->getTileSize().height*4),
                            color);
    }
    for (short int i = 0; i < 5 + 1; i++)
    {
        y = i * 16*4;
        draw_node->drawLine(Vec2(0, y),
                            Vec2(this->tileMap->getMapSize().width*this->tileMap->getTileSize().width*4, y),
                            color);
    }
    addChild(draw_node); 
}

void BattleScene::loadAllyUnits()
{
    std::vector<std::string> alliesNames{"archer_blue.png", "armorGuy_blue.png"};
    this->allies.resize(2);
    auto& cells = this->tileMap->getObjectGroup("ally")->getObjects();
    int i = 0;
    Vec2 desviation = Vec2(this->tileMap->getTileSize().width/2,this->tileMap->getTileSize().height/2);
    for (auto& obj : cells)
    {
        this->allies[i] = new Unit;
        //Create archer sprite
        this->allies[i]->unit = Sprite::createWithSpriteFrameName(alliesNames[i]);
        //Scale the sprite
        this->allies[i]->unit->setScale(4);
        //Set unit position on a tile -- tile attributes
        ValueMap& dict = obj.asValueMap();
        //Set position as the Tile center
        
        // *4 because the map is scaled x4
        this->allies[i]->position.set(Vec2(dict["xPos"].asInt(), dict["yPos"].asInt()));
        //Set sprite attr position
        
        int mapPos = dict["yPos"].asInt()*this->tileMap->getMapSize().width + dict["xPos"].asInt();
        this->allies[i]->unit->setPosition((this->map[mapPos]->position + desviation)*4);
        //Add to allies list
        addChild(this->allies[i]->unit);
        i++;
    }
}

void BattleScene::loadEnemyUnits()
{
    std::vector<std::string> enemiesNames{"archer_red.png", "armorGuy_red.png"};
    this->enemies.resize(2);
    auto& cells = this->tileMap->getObjectGroup("enemy")->getObjects();
    int i = 0;
    Vec2 desviation = Vec2(this->tileMap->getTileSize().width/2,this->tileMap->getTileSize().height/2);
    for (auto& obj : cells)
    {
        this->enemies[i] = new Unit;
        //Create archer sprite
        this->enemies[i]->unit = Sprite::createWithSpriteFrameName(enemiesNames[i]);
        //Scale the sprite
        this->enemies[i]->unit->setScale(4);
        //Set unit position on a tile -- tile attributes
        ValueMap& dict = obj.asValueMap();
        //Set position as the Tile center
        
        // *4 because the map is scaled x4
        this->enemies[i]->position.set(Vec2(dict["xPos"].asInt(), dict["yPos"].asInt()));
        //Set sprite attr position
        
        int mapPos = dict["yPos"].asInt()*this->tileMap->getMapSize().width + dict["xPos"].asInt();
        this->enemies[i]->unit->setPosition((this->map[mapPos]->position + desviation)*4);
        //Add to enemies list
        addChild(this->enemies[i]->unit);
        i++;
    }
}

/**
    Change turn and make things
**/
void BattleScene::changeTurn()
{
    if (this->turn)
    {

    } else
    {

    }
    this->turn = !this->turn;
}

/**
    Unit's action menu.
    Can move, attack (if enemy units at range) and wait.
**/
void BattleScene::actionMenu(Unit* unit, Unit* enemy)
{
    Vector<MenuItem*> unitMenu;
    auto moveItem = MenuItemFont::create("Move",
                                          CC_CALLBACK_0(Unit::move, unit, Vec2(0,0)) );
    auto attackItem = MenuItemFont::create("Attack",
                                          CC_CALLBACK_0(Unit::attack, unit, enemy) );
    //auto bagItem = MenuItemFont::create("Bag",
    //                                      NULL);
    auto waitItem = MenuItemFont::create("Wait",
                                          CC_CALLBACK_0(Unit::wait, this->allies[0]) );
    auto passItem = MenuItemFont::create("Pass",
                                          CC_CALLBACK_0(BattleScene::changeTurn, this) );
    if (unit == NULL)
    {
        moveItem->setEnabled(false);
        if (enemy == NULL)
        {
            attackItem->setEnabled(false);
        }
        //waitItem->setEnabled(false);
    }
    unitMenu.pushBack(moveItem);
    unitMenu.pushBack(attackItem);
    //unitMenu.pushBack(bagItem);
    unitMenu.pushBack(waitItem);
    unitMenu.pushBack(passItem);

    //log("%f", Director::getInstance()->getVisibleSize().width);
    //log("%f", Director::getInstance()->getWinSizeInPixels().width);
    //log("%f", Director::getInstance()->getOpenGLView()->getVisibleSize().width);
    //log("%f", Director::getInstance()->getOpenGLView()->getFrameSize().width);
    //log("%f", Director::getInstance()->getOpenGLView()->getVisibleRect().size.width);

    // create menu, it's an autorelease object
    auto menu = Menu::createWithArray(unitMenu);
    menu->alignItemsInRows(4);
    menu->alignItemsVertically();

    menu->setPosition(convertToNodeSpace(
                            Vec2(Director::getInstance()->getOpenGLView()->getFrameSize().width*0.8,
                                 Director::getInstance()->getOpenGLView()->getFrameSize().height/2)));
    menu->convertToNodeSpace(menu->getPosition());
    menu->setTag(66);


    // menu background
    auto draw_node = DrawNode::create();
    draw_node->drawSolidRect(convertToNodeSpace(
                                  Vec2(Director::getInstance()->getOpenGLView()->getFrameSize().width*0.65,
                                       Director::getInstance()->getOpenGLView()->getFrameSize().height*0.25)),
                             convertToNodeSpace(
                                  Vec2(Director::getInstance()->getOpenGLView()->getFrameSize().width*0.95,
                                       Director::getInstance()->getOpenGLView()->getFrameSize().height*0.75)),
                            Color4F(160,35,180,1));
    draw_node->convertToNodeSpace(draw_node->getPosition());
    draw_node->setTag(67);

    addChild(draw_node,2);
    addChild(menu,2);
    this->onMenu = true;
}

void BattleScene::addKeyboardEvents()
{
    // creating a keyboard event listener
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(BattleScene::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(BattleScene::onKeyReleased, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

// Implementation of the keyboard event callback function prototype
void BattleScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    if (!this->onMenu)
    {
        cellSelector(keyCode);
    } else
    {
        if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
        {
            this->onMenu = false;
            removeChildByTag(66);
            removeChildByTag(67);
        }
    }
}

void BattleScene::cellSelector(EventKeyboard::KeyCode keyCode)
{
    int max_x = this->tileMap->getMapSize().width;
    int max_y = this->tileMap->getMapSize().height;
    if ((keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW ||
            keyCode == EventKeyboard::KeyCode::KEY_A) &&
        this->selector.position.x > 0)
    {
        this->selector.position.x -= 1;
        this->selector.unit->setPosition((this->map[this->selector.position.y*
                                                this->tileMap->getMapSize().width +
                                                this->selector.position.x]->position + 
                                        Vec2(8,8))*4);
    }
    if ((keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW ||
            keyCode == EventKeyboard::KeyCode::KEY_D) &&
        this->selector.position.x < max_x-1)
    {
        this->selector.position.x += 1;
        this->selector.unit->setPosition((this->map[this->selector.position.y*
                                        this->tileMap->getMapSize().width +
                                        this->selector.position.x]->position + 
                                Vec2(8,8))*4);
    }
    if ((keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW ||
            keyCode == EventKeyboard::KeyCode::KEY_W) &&
        this->selector.position.y > 0)
    {
        this->selector.position.y -= 1;
        this->selector.unit->setPosition((this->map[this->selector.position.y*
                                        this->tileMap->getMapSize().width +
                                        this->selector.position.x]->position + 
                                Vec2(8,8))*4);
    }
    if ((keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW ||
            keyCode == EventKeyboard::KeyCode::KEY_S) &&
        this->selector.position.y < max_y-1)
    {
        this->selector.position.y += 1;
        this->selector.unit->setPosition((this->map[this->selector.position.y*
                                            this->tileMap->getMapSize().width +
                                            this->selector.position.x]->position + 
                                    Vec2(8,8))*4);
    }

    if (keyCode == EventKeyboard::KeyCode::KEY_ENTER)
    {
        actionMenu(NULL, NULL);
    }
}

void BattleScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
}
