#include "GameScene.h"
#include "GB2ShapeCache-x.h"

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h> 
#include "Cup.h"
//#include "Puck.h"
#include "Gate.h"
#include "Stick.h"
#include <string>

using namespace cocos2d;

#define PTM_RATIO 32

enum {
    kTagParentNode = 1,
	kGameRun = 2,
	kGameOver = 3,
};

enum {
  kBackground,
  kMiddleground,
  kForeground
};

GameScene::~GameScene() 
{  
   //delete m_debugDraw;
  /*
   if (_body)
   {  
     _world->DestroyBody(_body);  
     _body = NULL;  
   }
  */
   if (world) 
   {  
     delete world;  
     world = NULL;
	 delete _contactListener;
   }  
   
 }

Scene* GameScene::scene()
{
    Scene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        GameScene *layer = GameScene::create();

        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
		//layer->addChild(B2DebugDrawLayer::create(world, PTM_RATIO), 9999);
    } while (0);

    // return the scene
    return scene;
}

bool GameScene::init()
{
	//static int seed( StarterRand() );

    bool bRet = false;
    do 
    {
		srand (time(NULL));
		_puck = NULL;
		_stick = NULL;
		GameStatus = 1;
        _stickExist = false;
        _Score = 0;
        _cupBonus = 1;
		_iCups = 0;
		
        // load physics shapes
		GB2ShapeCache::sharedGB2ShapeCache()->addShapesWithFile("phisycs.plist");
    
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
        //CCLOG("*GameScene* SCREEN_HEIGHT = %d, SCREEN_WIDTH = %d, kScale = %f", SCREEN_HEIGHT, SCREEN_WIDTH, kScale);
        
        
		b2Vec2 gravity;
		gravity.Set(0.0f, 0.0f);
		world = new b2World(gravity);

		world->SetContinuousPhysics(true);    
		// Do we want to let bodies sleep?
		world->SetAllowSleeping(true);

		_contactListener = new MyContactListener();
		world->SetContactListener(_contactListener);

//================== BOARD =======================================================

		// 3. Add add a splash screen, show the cocos2d splash image.
        Sprite* spBG = Sprite::create("ice.png");
        CC_BREAK_IF(! spBG);

        // Place the sprite on the center of the screen
        spBG->setPosition(Point(SCREEN_WIDTH/2, SCREEN_HEIGHT/2));

		SCREEN_HEIGHT_DELTA = SCREEN_HEIGHT - spBG->getContentSize().height;
				
		// Create world
		//createWorld();
        spBG->setTag(2);
        spBG->setScale(kScale);
		// Add the sprite to HelloWorld layer as a child layer.
        this->addChild(spBG, 0);

//		Sprite* spBoard = new Sprite();
//		spBoard->setTag(2);
		
		// Create cup body 
		b2BodyDef BLBodyDef;
		BLBodyDef.type = b2_staticBody;
        BLBodyDef.position.Set(size.width/2/PTM_RATIO, size.height/2/PTM_RATIO);
        //BLBodyDef->setScale(kScale);
		//BLBodyDef.position.Set(0, 0);
        BLBodyDef.userData = spBG;
        b2Body * BLBody = world->CreateBody(&BLBodyDef);
        
		GB2ShapeCache *sc = GB2ShapeCache::sharedGB2ShapeCache();
		sc->addFixturesToBody(BLBody, "ice");
		spBG->setAnchorPoint(sc->anchorPointForShape("ice"));

        
        _ScoreLabel = CCLabelTTF::create("00", "Arial", 40);
        _ScoreLabel->setPosition(Point(size.width - 40, (size.height - 35)));
        _ScoreLabel->setColor(Color3B(255,0,0));
        this->addChild(_ScoreLabel);

//================== PUCK =======================================================

		Sprite *puck = Sprite::create("washer.png");
        //puck->setPosition(ccp(100,100));
        puck->setTag(1);
        puck->setScale(kScale);
        this->addChild(puck, 0);
		_puck = new Puck(puck, PTM_RATIO, world, kScale);

		//b2Vec2 force = b2Vec2(2, 1);
		//_puck->setApplyLinearImpulse(force, _puck->getBodyPos());

//================== GATE =======================================================
		// Gate
		Sprite *gate = Sprite::create("gate.png");
		//Sprite *gate = Sprite::create("gate.png", new CCRect::setRect( 0, 0, 32, 32));
		//gate->setPosition(ccp(size.width/2, pSprite->getPositionY() + 349));
        gate->setTag(4);
        gate->setScale(kScale);
        gate->setScaleX(2);
        this->addChild(gate, 0);

		//new Gate(gate, PTM_RATIO, SCREEN_WIDTH/2 * kScale, (spBG->getPositionY() + 349) * kScale, world, kScale);
        new Gate(gate, PTM_RATIO, SCREEN_WIDTH/2 * kScale, (SCREEN_HEIGHT/2 + 349) * kScale, world, kScale);

//================== CUP'S ======================================================
		
		Sprite *cup1 = Sprite::create("cup.png");
        cup1->setTag(3);
        cup1->setScale(kScale);
        this->addChild(cup1, 0);
		new Cup(cup1, 9, 3, world, kScale);

		Sprite *cup2 = Sprite::create("cup.png");
        cup2->setTag(3);
        cup2->setScale(kScale);
        this->addChild(cup2, 0);
		new Cup(cup2, 15, 9, world, kScale);

		Sprite *cup3 = Sprite::create("cup.png");
        cup3->setTag(3);
        cup3->setScale(kScale);
        this->addChild(cup3, 0);
		//Cup* _cup3 = new Cup(cup3, 22, 15, world);
        new Cup(cup3, 22, 15, world, kScale);
		
//================== ATLAS ======================================================
		SpriteFrameCache::getInstance()->
			addSpriteFramesWithFile("atlas.plist");
		_gameBatchNode = SpriteBatchNode::create("atlas.png");
		this->addChild(_gameBatchNode);

//================== MENU ======================================================
		// add a "close" icon to exit the progress. it's an autorelease object
//		CCMenuItemImage *pCloseItem = CCMenuItemImage::create("CloseNormal.png", "CloseSelected.png", this, menu_selector(GameScene::menuCloseCallback));
    
        auto pCloseItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(GameScene::menuCloseCallback, this));
        
		pCloseItem->setPosition(Point(size.width - pCloseItem->getContentSize().width/2 , pCloseItem->getContentSize().height/2));

		// create menu, it's an autorelease object
//		CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
        auto pMenu = Menu::create(pCloseItem, NULL);
		pMenu->setPosition(Point::ZERO);
		this->addChild(pMenu, 1);

        // Register Touch Event
        auto listener = EventListenerTouch::create(Touch::DispatchMode::ONE_BY_ONE);
        listener->setSwallowTouches(true);
        
        listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
        listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
        listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
        
        EventDispatcher::getInstance()->addEventListenerWithSceneGraphPriority(listener, this);
        
		scheduleUpdate();
		this->setTouchEnabled(true);

		//this->addChild(B2DebugDrawLayer::create(world, PTM_RATIO), 9999);
		// Or
		//B2DebugDrawLayer *dDraw;
		//dDraw= B2DebugDrawLayer::create(world, 32.0f);
		//this->addChild(dDraw,999);

		bRet = true;
    } while (0);

    return bRet;
}

void GameScene::update(float dt)
{
	std::vector<b2Body *>toDestroy;
    std::vector<MyContact>::iterator pos;

    world->Step(dt, 8, 1);
	//world->DrawDebugData();
    for(b2Body *b = world->GetBodyList(); b; b=b->GetNext()) {
		// Create Stick
		if (GameStatus == 2 && _startPoint.x != _endPoint.x && _startPoint.y != _endPoint.y){
			// destroy stick
            if (_stickExist){
				toDestroy.push_back(_stick->getBody());

                _stickExist = false;
			} 
            
            // Create stick
            Sprite *_spStick = Sprite::create("stick.png");
            _spStick->setTag(6);
            _spStick->setScale(kScale);
            this->addChild(_spStick);
            _stick = new Stick(_spStick, PTM_RATIO, _startPoint, _endPoint, 0, world, kScale);
            _stickExist = true;
            _startPoint = _endPoint;

		}

        if (b->GetUserData() != NULL) {
            //Synchronize the AtlasSprites position and rotation with the corresponding body
            Sprite* myActor = (Sprite*)b->GetUserData();

//			myActor->setPosition( CCPointMake( b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO) );
            myActor->setPosition( Point( b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO) );
			myActor->setRotation( -1 * CC_RADIANS_TO_DEGREES(b->GetAngle()) );
        }
    }
    
	// Destroy body
    for (pos=_contactListener->_contacts.begin();
         pos != _contactListener->_contacts.end(); ++pos) {
        MyContact contact = *pos;
        /*
        if ((contact.fixtureA == _bottomFixture && contact.fixtureB == _ballFixture) ||
            (contact.fixtureA == _ballFixture && contact.fixtureB == _bottomFixture)) {
            //NSLog(@"Ball hit bottom!");
            CCScene *gameOverScene = [GameOverLayer sceneWithWon:NO];
            [[CCDirector sharedDirector] replaceScene:gameOverScene];
        }
        */

        b2Body *bodyA = contact.fixtureA->GetBody();
        b2Body *bodyB = contact.fixtureB->GetBody();
        if (bodyA->GetUserData() != NULL && bodyB->GetUserData() != NULL) {
            Sprite* spriteA = (Sprite *) bodyA->GetUserData();
            Sprite* spriteB = (Sprite *) bodyB->GetUserData();
 
            //Sprite A = ball, Sprite B = Cup
            if (spriteA->getTag() == 1 && spriteB->getTag() == 3) {
                if (std::find(toDestroy.begin(), toDestroy.end(), bodyB) == toDestroy.end()) {
                    toDestroy.push_back(bodyB);
                    playerScore (5 * _cupBonus);
                    _cupBonus++ ;
					_iCups++;
                }
            }
            
            //Sprite A = Cup, Sprite B = ball
            else if (spriteA->getTag() == 3 && spriteB->getTag() == 1) {
                if (std::find(toDestroy.begin(), toDestroy.end(), bodyA) == toDestroy.end()) {
                    toDestroy.push_back(bodyA);
                    playerScore (5 * _cupBonus);
                    _cupBonus++ ;
					_iCups++;
                }
            }

			// Goal
			//Sprite A = ball, Sprite B = sensor
            if (spriteA->getTag() == 1 && spriteB->getTag() == 5) {
                if (std::find(toDestroy.begin(), toDestroy.end(), bodyB) == toDestroy.end()) {
                    toDestroy.push_back(bodyA);
					_puck->setVelocity(b2Vec2_zero);
					GameStatus = 3;
					GameEnd(true);
                    //new GameWinScene();
                }
            }
            
            //Sprite A = Sensor, Sprite B = ball
            else if (spriteA->getTag() == 5 && spriteB->getTag() == 1) {
                if (std::find(toDestroy.begin(), toDestroy.end(), bodyA) == toDestroy.end()) {
                    toDestroy.push_back(bodyB);
					_puck->setVelocity(b2Vec2_zero);
					GameStatus = 3;
					GameEnd(true);
                    //new GameWinScene();
                }
            }

			//Sprite A = ball, Sprite B = Stick
            if (spriteA->getTag() == 1 && spriteB->getTag() == 6) {
                if (std::find(toDestroy.begin(), toDestroy.end(), bodyB) == toDestroy.end()) {
                    toDestroy.push_back(bodyB);
                    _stickExist = false;
                    _cupBonus = 1;
					//world->DestroyBody(_stick->getBody());
                }
            }
            
            //Sprite A = Stick, Sprite B = ball
            else if (spriteA->getTag() == 6 && spriteB->getTag() == 1) {
                if (std::find(toDestroy.begin(), toDestroy.end(), bodyA) == toDestroy.end()) {
                    toDestroy.push_back(bodyA);
                    _stickExist = false;
                    _cupBonus = 1;
					//world->DestroyBody(_stick->getBody());					
                }
            }
        }
    }
    
    std::vector<b2Body *>::iterator pos2;
    for (pos2 = toDestroy.begin(); pos2 != toDestroy.end(); ++pos2) {
        b2Body *body = *pos2;
        if (body->GetUserData() != NULL) {
            Sprite *sprite = (Sprite *) body->GetUserData();
            //[self removeChild:sprite cleanup:YES];
			this->removeChild(sprite, true);
        }
        world->DestroyBody(body);
    }

}

void GameScene::menuCloseCallback(Object* pSender)
{
    //CCDirector::sharedDirector()->end();
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

bool GameScene::onTouchBegan (cocos2d::Touch *touch, cocos2d::Event *event){
//    CCTouch* touch = (CCTouch*)( touch->anyObject() );
//    CCPoint location = touch->getLocationInView();
//    location = CCDirector::sharedDirector()->convertToGL(location);

    Point location = touch->getLocationInView();
    
    location = Director::getInstance()->convertToGL(location);
    
    _startPoint = location;
    _endPoint = location;
    //CCLog(  location.x);
    return true;
}

void GameScene::onTouchMoved (cocos2d::Touch *touch, cocos2d::Event *event){
    
}
void GameScene::onTouchEnded (cocos2d::Touch *touch, cocos2d::Event *event){
    //CCLog("this up");
    Point location = touch->getLocationInView();
    location = Director::getInstance()->convertToGL(location);
	_endPoint = location;
	if (GameStatus == 1){
		_puck->setApplyLinearImpulse(b2Vec2((location.x - _puck->getBodyPos().x*PTM_RATIO)/PTM_RATIO, (location.y - _puck->getBodyPos().y*PTM_RATIO)/PTM_RATIO));
        _startPoint = _endPoint;
		GameStatus = 2;
		//this->schedule(schedule_selector(GameScene::GameTimer), 1.0f);
	}
}

void GameScene::onTouchCancelled (cocos2d::Touch *touch, cocos2d::Event *event){
    
}

void GameScene::playerScore (int sc) {
    //SimpleAudioEngine::sharedEngine()->playEffect("score.wav");
    char score_buffer[10];

    _Score = _Score + sc;
    sprintf(score_buffer,"%i", _Score);
    _ScoreLabel->setString(score_buffer);    
    
    String * score = String::createWithFormat("%i", _Score);
    _ScoreLabel->setString(score->getCString());

}

void GameScene::GameEnd(bool _win) {
	Sprite *spSB, *spCups, *spText, *spTime1, *spTime2,*spTotal1,*spTotal2;

	spSB = Sprite::createWithSpriteFrameName("scoreboard.png");
	spSB->setPosition(Point(SCREEN_WIDTH/2, SCREEN_HEIGHT/2));

	float k = SCREEN_WIDTH/spSB->getBoundingBox().size.width;

	spSB->setScale(k * 0.95);
	//_sprite->boundingBox()
	_gameBatchNode->addChild(spSB);

	// Text
	if(_win){
		spText = Sprite::createWithSpriteFrameName("yuo_win.png");
		spText->setPosition(Point(SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + 36 * k));
		spText->setScale(k * 0.93);
	}else{
		spText = Sprite::createWithSpriteFrameName("game_over.png");
		spText->setPosition(Point(SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + 36 * k));
		spText->setScale(k * 0.93);
	}

	_gameBatchNode->addChild(spText);

	// Cups
	char text[256];
		
	sprintf(text,"%d.png", _iCups);
    spCups = Sprite::createWithSpriteFrameName(text);	
	spCups->setPosition(Point(SCREEN_WIDTH/2 - 90 * k, SCREEN_HEIGHT/2 - 27 * k));
	spCups->setScale(k * 0.95);
	_gameBatchNode->addChild(spCups);

	// Time
	text[256];
	int iTime = 0;

	sprintf(text,"%d.png", iTime);
    spTime1 = Sprite::createWithSpriteFrameName(text);	
	spTime1->setPosition(Point(SCREEN_WIDTH/2 - 15 * k, SCREEN_HEIGHT/2 - 27 * k));
	spTime1->setScale(k * 0.95);

	sprintf(text,"%d.png", iTime);
    spTime2 = Sprite::createWithSpriteFrameName(text);	
	spTime2->setPosition(Point(SCREEN_WIDTH/2 + 15 * k, SCREEN_HEIGHT/2 - 27 * k));
	spTime2->setScale(k * 0.95);

	_gameBatchNode->addChild(spTime1);
	_gameBatchNode->addChild(spTime2);

	// Total
	text[256];
	int iTotal = 0;

	sprintf(text,"%d.png", (iTotal + _Score)/10);
    spTotal1 = Sprite::createWithSpriteFrameName(text);	
	spTotal1->setPosition(Point(SCREEN_WIDTH/2 + 66 * k, SCREEN_HEIGHT/2 - 27 * k));
	spTotal1->setScale(k * 0.95);

	sprintf(text,"%d.png", (iTotal + _Score)%10);
    spTotal2 = Sprite::createWithSpriteFrameName(text);	
	spTotal2->setPosition(Point(SCREEN_WIDTH/2 + 96 * k, SCREEN_HEIGHT/2 - 27 * k));
	spTotal2->setScale(k * 0.95);

	_gameBatchNode->addChild(spTotal1);
	_gameBatchNode->addChild(spTotal2);
}

void GameScene::GameTimer(){

}

void GameScene::resetGame(void){

}