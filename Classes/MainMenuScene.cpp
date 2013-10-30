#include "MainMenuScene.h"
#include "GameScene.h"
#include "MenuLevelScene.h"

using namespace cocos2d;

Scene* MainMenu::scene()
{
    Scene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        MainMenu *layer = MainMenu::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
    bool bRet = false;
    do 
    {
        // Get window size and place the label upper.
        Size size = Director::getInstance()->getWinSize();
        
        SCREEN_HEIGHT = size.height;
		SCREEN_WIDTH = size.width;
        kScale = 1.0f;
        
        if(SCREEN_WIDTH / 480.0f * 800.0f <= SCREEN_HEIGHT){
            kScale = SCREEN_WIDTH/480.0f;
        }else{
            kScale = SCREEN_HEIGHT/800.0f;
        }
        //CCLOG("SCREEN_HEIGHT = %d, SCREEN_WIDTH = %d, kScale = %f", SCREEN_HEIGHT, SCREEN_WIDTH, kScale);
        
		// Create button start
		auto *pStart = MenuItemImage::create("Start.png", "Start.png", CC_CALLBACK_1(MainMenu::menuStartCallback, this));
		pStart->setPosition(Point(CCDirector::getInstance()->getWinSize().width/2, 150 * kScale));
        pStart->setScale(kScale);
        
		// Create button exit
        auto *pExit = MenuItemImage::create("Exit.png", "Exit.png", CC_CALLBACK_1(MainMenu::menuExitCallback, this));

        pExit->setScale(kScale);
		pExit->setPosition(Point(CCDirector::getInstance()->getWinSize().width/2, 70 * kScale));

		auto *pMenu = CCMenu::create(pExit,pStart, NULL);
		pMenu->setPosition(Point::ZERO);
		CC_BREAK_IF(! pMenu);

        // Add the menu to HelloWorld layer as a child layer.
        this->addChild(pMenu, 1);

        // 2. Add a label shows "Hello World".

        // Create a label and initialize with string "Hello World".
        //CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
        //CC_BREAK_IF(! pLabel);
        
        //pLabel->setPosition(ccp(size.width / 2, size.height - 50));

        // Add the label to HelloWorld layer as a child layer.
        //this->addChild(pLabel, 1);

        // 3. Add add a splash screen, show the cocos2d splash image.
        Sprite* spBG = Sprite::create("MainMenu.png");
        CC_BREAK_IF(! spBG);

        // Place the sprite on the center of the screen
        spBG->setPosition(Point(size.width/2, size.height/2));
        spBG->setScale(kScale);
        // Add the sprite to HelloWorld layer as a child layer.
        this->addChild(spBG, 0);

        bRet = true;
    } while (0);

    return bRet;
}

void MainMenu::menuStartCallback(Object* pSender)
{
    // "close" menu item clicked
    //CCDirector::sharedDirector()->end();
    //MenuLevel::setkScale(kScale);
	Director::getInstance()->replaceScene(MenuLevel::scene());
}

void MainMenu::menuExitCallback(Object* pSender)
{
    // "close" menu item clicked
    Director::getInstance()->end();
}