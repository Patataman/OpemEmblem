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

    this->state = 0;
    this->rectsDrew = 0;
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
        //Default weapon
        this->allies[i]->weapon = new Item("Wooden Sword", 5, 75, 1);
        //Set unit position on a tile -- tile attributes
        ValueMap& dict = obj.asValueMap();
        this->allies[i]->position.set(Vec2(dict["xPos"].asInt(), dict["yPos"].asInt()));        
        
        int mapPos = dict["yPos"].asInt()*this->tileMap->getMapSize().width + dict["xPos"].asInt();
        //Set sprite attr position
        // *4 because the map is scaled x4
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
        //Default weapon
        this->enemies[i]->weapon = new Item("Wooden Sword", 5, 75, 1);
        //Set unit position on a tile -- tile attributes
        ValueMap& dict = obj.asValueMap();
        this->enemies[i]->position.set(Vec2(dict["xPos"].asInt(), dict["yPos"].asInt()));
        
        int mapPos = dict["yPos"].asInt()*this->tileMap->getMapSize().width + dict["xPos"].asInt();
        //Set sprite attr position
        // *4 because the map is scaled x4
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


//Move unit action
void BattleScene::moveUnit(Unit* unit)
{
    log("MOVE");
    int max_x = this->tileMap->getMapSize().width;
    int max_y = this->tileMap->getMapSize().height;

    for (int i=1; i<= unit->movement; i++)
    {
        for (int j=1; j<= unit->movement; j++)
        {
            Vec2 desviation = Vec2(this->tileMap->getTileSize().width/2,this->tileMap->getTileSize().height/2);
            if (unit->position.x - i >= 0 && unit->position.y - j >= 0 &&
                sqrt(pow(i, 2) + pow(j,2)) <= unit->movement)
            {
                int mapPos = (unit->position.y-j)*max_x + unit->position.x-i;

                auto draw_node = DrawNode::create();
                draw_node->drawSolidRect(Vec2(0,0),
                                         Vec2(this->tileMap->getTileSize().width*4, this->tileMap->getTileSize().height*4),
                                         Color4F(165,124,20,0.5));
                draw_node->setTag(70);
                draw_node->setPosition((this->map[mapPos]->position)*4);

                this->rectsDrew++;

                addChild(draw_node,-1);
            }
            if (unit->position.x + i < max_x && unit->position.y + j < max_y &&
                sqrt(pow(i, 2) + pow(j,2)) <= unit->movement)
            {
                int mapPos = (unit->position.y+j)*max_x + unit->position.x+i;

                auto draw_node = DrawNode::create();
                draw_node->drawSolidRect(Vec2(0,0),
                                         Vec2(this->tileMap->getTileSize().width*4, this->tileMap->getTileSize().height*4),
                                         Color4F(165,124,20,0.5));
                draw_node->setTag(70);
                draw_node->setPosition((this->map[mapPos]->position)*4);

                this->rectsDrew++;

                addChild(draw_node,-1);
            }
            if (unit->position.x - i >= 0 && unit->position.y + j < max_y &&
                sqrt(pow(i, 2) + pow(j,2)) <= unit->movement)
            {
                int mapPos = (unit->position.y+j)*max_x + unit->position.x-i;

                auto draw_node = DrawNode::create();
                draw_node->drawSolidRect(Vec2(0,0),
                                         Vec2(this->tileMap->getTileSize().width*4, this->tileMap->getTileSize().height*4),
                                         Color4F(165,124,20,0.5));
                draw_node->setTag(70);
                draw_node->setPosition((this->map[mapPos]->position)*4);

                this->rectsDrew++;

                addChild(draw_node,-1);
            }
            if (unit->position.x + i < max_x && unit->position.y - j >= 0 &&
                sqrt(pow(i, 2) + pow(j,2)) <= unit->movement)
            {
                int mapPos = (unit->position.y-j)*max_x + unit->position.x+i;

                auto draw_node = DrawNode::create();
                draw_node->drawSolidRect(Vec2(0,0),
                                         Vec2(this->tileMap->getTileSize().width*4, this->tileMap->getTileSize().height*4),
                                         Color4F(165,124,20,0.5));
                draw_node->setTag(70);
                draw_node->setPosition((this->map[mapPos]->position)*4);

                this->rectsDrew++;

                addChild(draw_node,-1);
            }
        }
    }
    for (int i=1; i<= unit->movement; i++)
    {
        if (unit->position.x + i < max_x)
        {
            int mapPos = (unit->position.y)*max_x + unit->position.x+i;

            auto draw_node = DrawNode::create();
            draw_node->drawSolidRect(Vec2(0,0),
                                     Vec2(this->tileMap->getTileSize().width*4, this->tileMap->getTileSize().height*4),
                                     Color4F(165,124,20,0.5));
            draw_node->setTag(70);
            draw_node->setPosition((this->map[mapPos]->position)*4);

            this->rectsDrew++;

            addChild(draw_node,-1);
        }
        if (unit->position.x - i >= 0)
        {
            int mapPos = (unit->position.y)*max_x + unit->position.x-i;

            auto draw_node = DrawNode::create();
            draw_node->drawSolidRect(Vec2(0,0),
                                     Vec2(this->tileMap->getTileSize().width*4, this->tileMap->getTileSize().height*4),
                                     Color4F(165,124,20,0.5));
            draw_node->setTag(70);
            draw_node->setPosition((this->map[mapPos]->position)*4);

            this->rectsDrew++;

            addChild(draw_node,-1);
        }
        if (unit->position.y - i >= 0)
        {
            int mapPos = (unit->position.y-i)*max_x + unit->position.x;

            auto draw_node = DrawNode::create();
            draw_node->drawSolidRect(Vec2(0,0),
                                     Vec2(this->tileMap->getTileSize().width*4, this->tileMap->getTileSize().height*4),
                                     Color4F(165,124,20,0.5));
            draw_node->setTag(70);
            draw_node->setPosition((this->map[mapPos]->position)*4);

            this->rectsDrew++;

            addChild(draw_node,-1);
        }
        if (unit->position.y + i < max_y)
        {
            int mapPos = (unit->position.y+i)*max_x + unit->position.x;

            auto draw_node = DrawNode::create();
            draw_node->drawSolidRect(Vec2(0,0),
                                     Vec2(this->tileMap->getTileSize().width*4, this->tileMap->getTileSize().height*4),
                                     Color4F(165,124,20,0.5));
            draw_node->setTag(70);
            draw_node->setPosition((this->map[mapPos]->position)*4);

            this->rectsDrew++;

            addChild(draw_node,-1);
        }
    }
    this->state = 2;
}

//Attack unit action
void BattleScene::attackUnit(Unit* unit)
{
    this->state = 3;
}

/**
    Unit's action menu.
    Can move, attack (if enemy units at range) and wait.
**/
void BattleScene::actionMenu(Unit* unit, bool enemy)
{
    Vector<MenuItem*> unitMenu;
    auto moveItem = MenuItemFont::create("Move",
                                          CC_CALLBACK_0(BattleScene::moveUnit, this, unit) );
    auto attackItem = MenuItemFont::create("Attack",
                                          CC_CALLBACK_0(BattleScene::attackUnit, this, unit) );
    //auto bagItem = MenuItemFont::create("Bag",
    //                                      nullptr);
    auto waitItem = MenuItemFont::create("Wait",
                                          CC_CALLBACK_0(Unit::wait, unit) );
    auto passItem = MenuItemFont::create("Pass",
                                          CC_CALLBACK_0(BattleScene::changeTurn, this) );
    if (unit == nullptr)
    {
        moveItem->setEnabled(false);
        waitItem->setEnabled(false);
    }
    if (unit != nullptr && enemy)
    {
        unitMenu.pushBack(attackItem);
    }
    unitMenu.pushBack(moveItem);
    //unitMenu.pushBack(bagItem);
    unitMenu.pushBack(waitItem);
    unitMenu.pushBack(passItem);

    //create menu, it's an autorelease object
    auto menu = Menu::createWithArray(unitMenu);
    menu->alignItemsInRows(unitMenu.size());
    menu->alignItemsVertically();

    menu->setPosition(convertToNodeSpace(
                            Vec2(Director::getInstance()->getOpenGLView()->getFrameSize().width*0.8,
                                 Director::getInstance()->getOpenGLView()->getFrameSize().height/2)));
    menu->convertToNodeSpace(menu->getPosition());
    menu->setTag(66);


    //menu background
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
    this->state = 1;
}

void BattleScene::addKeyboardEvents()
{
    // creating a keyboard event listener
    auto listenerKeyboard = EventListenerKeyboard::create();
    listenerKeyboard->onKeyPressed = CC_CALLBACK_2(BattleScene::onKeyPressed, this);
    listenerKeyboard->onKeyReleased = CC_CALLBACK_2(BattleScene::onKeyReleased, this);

    // creating a mouse event listener
    auto listenerMouse = EventListenerMouse::create();
    listenerMouse->onMouseUp = CC_CALLBACK_0(BattleScene::onMouseUp, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeyboard, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerMouse, this);
}

// Implementation of the keyboard event when key is pressed
void BattleScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    if (this->state != 1)
    {
        cellSelector(keyCode);
        if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
        {
            while (this->rectsDrew > 0) { removeChildByTag(70); this->rectsDrew--;}
            this->state = 0;
        }
    } else
    {
        if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
        {
            this->state = 0;
            removeChildByTag(66);
            removeChildByTag(67);
        }
    }
}

// On mouse up events
void BattleScene::onMouseUp()
{
    if (this->state)
    {
        auto menu = getChildByTag(66);
        for (int i=0; i<menu->getChildren().size(); i++)
        {
            MenuItem* nodo = (MenuItem*) menu->getChildren().at(i);
            if (nodo->isRunning())
            {
                removeChildByTag(66);
                removeChildByTag(67);
                break;
            }
        }
    }
}

void BattleScene::cellSelector(EventKeyboard::KeyCode keyCode)
{
    int max_x = this->tileMap->getMapSize().width;
    int max_y = this->tileMap->getMapSize().height;
    //Move left
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
    //Move right
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
    //Move up
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
    //Move down
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

    //When Enter is pressed and state = 0:
    if (keyCode == EventKeyboard::KeyCode::KEY_ENTER && this->state == 0)
    {
        log("state %d", this->state);
        //Check if you're pressing Enter on an ally unit
        Unit* ally = nullptr;
        bool enemy = false;
        for (int i=0; i<this->allies.size(); i++)
        {
            if (this->allies.at(i)->position == this->selector.position)
            {
                ally = this->allies.at(i);
                break;
            }
        }
        //If you find an ally, now check if there's a enemy near.
        if (ally != nullptr)
        {
            for (int i=0; i<this->enemies.size(); i++)
            {
                if (sqrt(pow(ally->position.x - this->enemies.at(i)->position.x, 2) +
                    pow(ally->position.y - this->enemies.at(i)->position.y,2) <= ally->weapon->range))
                {
                    enemy = true;
                    break;
                }
            }
        }
        actionMenu(ally, enemy);
    }
}

void BattleScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
}
