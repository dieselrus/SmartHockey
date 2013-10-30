//
//  GameWinScene.cpp
//  HelloCpp
//
//  Created by admin on 20.10.13.
//
//

#include "GameWinScene.h"
#include "GameScene.h"

using namespace cocos2d;

Scene* GameWinScene::scene()
{
    Scene * scene = NULL;
    do
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);
        
        // 'layer' is an autorelease object
        GameWinScene *layer = GameWinScene::create();
        CC_BREAK_IF(! layer);
        
        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);
    
    // return the scene
    return scene;
}

//GameWinScene::GameWinScene(int _cup, int _time, int _score){
//    
//}
//
//GameWinScene::~GameWinScene(){
//    
//}

bool GameWinScene::init()
{
    bool bRet = false;
    do
    {
		// Create button start
		auto *pReload = MenuItemImage::create("Start.png", "Start.png", CC_CALLBACK_1(GameWinScene::menuReloadCallback, this));
		pReload->setPosition(Point(Director::getInstance()->getWinSize().width/2, 150));
        
		// Create button exit
		auto *pExit = MenuItemImage::create("Exit.png", "Exit.png", CC_CALLBACK_1(GameWinScene::menuNextCallback, this));
		pExit->setPosition(Point(CCDirector::getInstance()->getWinSize().width/2, 70));
        
		auto *pMenu = Menu::create(pExit,pReload, NULL);
		pMenu->setPosition(Point::ZERO);
		CC_BREAK_IF(! pMenu);
        
        // Add the menu to HelloWorld layer as a child layer.
        this->addChild(pMenu, 1);
        
        // 2. Add a label shows "Hello World".
        
        // Create a label and initialize with string "Hello World".
        //CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
        //CC_BREAK_IF(! pLabel);
        
        // Get window size and place the label upper.
        Size size = Director::getInstance()->getWinSize();
        //pLabel->setPosition(ccp(size.width / 2, size.height - 50));
        
        SCREEN_HEIGHT = size.height;
		SCREEN_WIDTH = size.width;
        
		kScaleX = SCREEN_WIDTH/480;
        
        // Add the label to HelloWorld layer as a child layer.
        //this->addChild(pLabel, 1);
        
        // 3. Add add a splash screen, show the cocos2d splash image.
        Sprite* pSprite = Sprite::create("MainMenu.png");
        CC_BREAK_IF(! pSprite);
        
        // Place the sprite on the center of the screen
        pSprite->setPosition(Point(size.width/2, size.height/2));
        
        // Add the sprite to HelloWorld layer as a child layer.
        this->addChild(pSprite, 0);
        
        createScoreBoard(3, 60, 60);
        
        bRet = true;
    } while (0);
    
    return bRet;
}

void GameWinScene::createScoreBoard(int _cup, int _time, int _score) {
	Sprite *spSB, *spCups, *spText, *spTime1, *spTime2,*spTotal1,*spTotal2;
    
//================== ATLAS ======================================================
    SpriteFrameCache::getInstance()->
    addSpriteFramesWithFile("atlas.plist");
    SpriteBatchNode *_gameBatchNode = SpriteBatchNode::create("atlas.png");
    this->addChild(_gameBatchNode);
    
	spSB = Sprite::createWithSpriteFrameName("scoreboard.png");
	spSB->setPosition(Point(SCREEN_WIDTH/2, SCREEN_HEIGHT/2));
    
	float k = SCREEN_WIDTH/spSB->getBoundingBox().size.width;
    
	spSB->setScale(k * 0.95);
	//_sprite->boundingBox()
	_gameBatchNode->addChild(spSB);
    
	// Text
    spText = Sprite::createWithSpriteFrameName("yuo_win.png");
    spText->setPosition(Point(SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + 36 * k));
    spText->setScale(k * 0.93);
    
	_gameBatchNode->addChild(spText);
    
	// Cups
	char text[256];
    
	sprintf(text,"%d.png", _cup);
    spCups = Sprite::createWithSpriteFrameName(text);
	spCups->setPosition(Point(SCREEN_WIDTH/2 - 90 * k, SCREEN_HEIGHT/2 - 27 * k));
	spCups->setScale(k * 0.95);
	_gameBatchNode->addChild(spCups);
    
	// Time
	text[256];
	//int iTime = 0;
    
	sprintf(text,"%d.png", _time);
    spTime1 = Sprite::createWithSpriteFrameName(text);
	spTime1->setPosition(Point(SCREEN_WIDTH/2 - 15 * k, SCREEN_HEIGHT/2 - 27 * k));
	spTime1->setScale(k * 0.95);
    
	sprintf(text,"%d.png", _time);
    spTime2 = Sprite::createWithSpriteFrameName(text);
	spTime2->setPosition(Point(SCREEN_WIDTH/2 + 15 * k, SCREEN_HEIGHT/2 - 27 * k));
	spTime2->setScale(k * 0.95);
    
	_gameBatchNode->addChild(spTime1);
	_gameBatchNode->addChild(spTime2);
    
	// Total
	text[256];
	int iTotal = 0;
    
	sprintf(text,"%d.png", (iTotal + _score)/10);
    spTotal1 = Sprite::createWithSpriteFrameName(text);
	spTotal1->setPosition(Point(SCREEN_WIDTH/2 + 66 * k, SCREEN_HEIGHT/2 - 27 * k));
	spTotal1->setScale(k * 0.95);
    
	sprintf(text,"%d.png", (iTotal + _score)%10);
    spTotal2 = Sprite::createWithSpriteFrameName(text);
	spTotal2->setPosition(Point(SCREEN_WIDTH/2 + 96 * k, SCREEN_HEIGHT/2 - 27 * k));
	spTotal2->setScale(k * 0.95);
    
	_gameBatchNode->addChild(spTotal1);
	_gameBatchNode->addChild(spTotal2);
}

void GameWinScene::menuReloadCallback(Object* pSender)
{
    // "close" menu item clicked
    //CCDirector::sharedDirector()->end();
	Director::getInstance()->replaceScene(GameScene::scene());
}

void GameWinScene::menuNextCallback(Object* pSender)
{
    // "close" menu item clicked
    Director::getInstance()->end();
}