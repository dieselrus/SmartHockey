//
//  MenuLevelScene.cpp
//  HelloCpp
//
//  Created by diesel on 23.09.13.
//
//

#include "MenuLevelScene.h"
#include "GameScene.h"

using namespace cocos2d;

#define PTM_RATIO 32

Scene* MenuLevel::scene()
{
    Scene * scene = NULL;
    do
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);
        
        // 'layer' is an autorelease object
        MenuLevel *layer = MenuLevel::create();
        CC_BREAK_IF(! layer);
        
        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MenuLevel::init()
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
        //CCLOG("*MenuLevel* SCREEN_HEIGHT = %d, SCREEN_WIDTH = %d, kScale = %f", SCREEN_HEIGHT, SCREEN_WIDTH, kScale);
        
        
        //pLabel->setPosition(ccp(size.width / 2, size.height - 50));
        
        // Add the label to HelloWorld layer as a child layer.
        //this->addChild(pLabel, 1);
        
        // 3. Add add a splash screen, show the cocos2d splash image.
        Sprite* spBG = Sprite::create("MenuLevel.png");
        CC_BREAK_IF(! spBG);
        
        // Place the sprite on the center of the screen
        spBG->setPosition(Point(size.width/2, size.height/2));
        spBG->setScale(kScale);
        // Add the sprite to HelloWorld layer as a child layer.
        this->addChild(spBG, 0);

        int _lvl = 1;
		//for(int i = 1; i <=3; i++){
		//	for(int j = 1; j<=5; j++){
		//		createMenuLevel((i*size.width/4), (j*size.height/6), _lvl);
		//		_lvl++;
		//	}
		//}
		for(int j = 1; j<=5; j++){
			for(int i = 1; i <=3; i++){			
				createMenuLevel((i * SCREEN_WIDTH/4), ((SCREEN_HEIGHT - j*SCREEN_HEIGHT/6)), _lvl);
				_lvl++;
			}
		}

        // Register Touch Event
        auto listener = EventListenerTouch::create(Touch::DispatchMode::ONE_BY_ONE);
        listener->setSwallowTouches(true);
        
        listener->onTouchBegan = CC_CALLBACK_2(MenuLevel::onTouchBegan, this);
        listener->onTouchMoved = CC_CALLBACK_2(MenuLevel::onTouchMoved, this);
        listener->onTouchEnded = CC_CALLBACK_2(MenuLevel::onTouchEnded, this);
        
        EventDispatcher::getInstance()->addEventListenerWithSceneGraphPriority(listener, this);
        
        this->setTouchEnabled(true);
        
        bRet = true;
    } while (0);
    
    return bRet;
}

bool MenuLevel::onTouchBegan (cocos2d::Touch *touch, cocos2d::Event *event){
    //CCLog("this down");
    return true;
}
void MenuLevel::onTouchMoved (cocos2d::Touch *touch, cocos2d::Event *event){
    
}
void MenuLevel::onTouchEnded (cocos2d::Touch *touch, cocos2d::Event *event){
    //CCLog("this up");
    Director::getInstance()->replaceScene(GameScene::scene());
}
void MenuLevel::onTouchCancelled (cocos2d::Touch *touch, cocos2d::Event *event){
    
}

void MenuLevel::menuStartCallback(Object* pSender)
{
    // "close" menu item clicked
    //CCDirector::sharedDirector()->end();
	Director::getInstance()->replaceScene(GameScene::scene());
}

void MenuLevel::menuExitCallback(Object* pSender)
{
    // "close" menu item clicked
    Director::getInstance()->end();
}

void MenuLevel::createMenuLevel(float _x, float _y, int _level)
{
	Sprite* _rect = Sprite::create("rect.png");
	_rect->setPosition(Point(_x,_y));
    _rect->setScale(kScale);
	this->addChild(_rect, 0);

	//CCLabelTTF* _LevelNum;
	//CCString * score = CCString::createWithFormat("%i", _level);
    //_LevelNum->setString(score->getCString());

	LabelTTF* _LevelNum = LabelTTF::create("00", "Arial Bold", 83);
	String * score = String::createWithFormat("%i", _level);
    _LevelNum->setString(score->getCString());
	_LevelNum->setPosition(Point(_x, _y));
    _LevelNum->setScale(kScale);
	_LevelNum->setColor(Color3B(255,255,255));
	this->addChild(_LevelNum);
}

//void MenuLevel::setkScale(float k){
//    kScale = k;
//}