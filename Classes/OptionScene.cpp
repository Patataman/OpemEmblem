#include "MainScene.h"
#include "OptionScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* OptionScene::createScene()
{
    return OptionScene::create();
}

// on "init" you need to initialize your instance
bool OptionScene::init()
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
    Vector<MenuItem*> optionMenu;

    auto checkbox = ui::CheckBox::create("checkbox/check_box_normal.png",
                                 "checkbox/check_box_normal_press.png",
                                 "checkbox/check_box_active.png",
                                 "checkbox/check_box_normal_disable.png",
                                 "checkbox/check_box_active_disable.png");

    checkbox->addEventListener(NULL);


    auto musicItem = MenuItemFont::create("Music",
                                            NULL);
    optionMenu.pushBack(musicItem);
    
    // create menu, it's an autorelease object
    auto menu = Menu::createWithArray(optionMenu);
//  menu->setPosition(Vec2(visibleSize.width - menu->getContentSize().width/2,
//                      visibleSize.height - menu->getContentSize().height/2));
    menu->alignItemsInRows(1);
    menu->alignItemsVertically();

    checkbox->setPosition(menu->getPosition() + Vec2(musicItem->getContentSize().width,0));

    auto backItem = MenuItemFont::create("Back",
                                            CC_CALLBACK_0(OptionScene::backToMenu, this));
    auto menuBack = Menu::create(backItem, NULL);
    menuBack->setPosition(Vec2::ZERO);

    backItem->setPosition(Vec2(10 + backItem->getContentSize().width,
                            10 + backItem->getContentSize().height));

    this->addChild(menu, 1);
    this->addChild(menuBack,1);
    this->addChild(checkbox, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Options 0.1a", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    return true;
}

void OptionScene::backToMenu()
{
    //go back to menu
    Director::getInstance()->popScene(); 
}