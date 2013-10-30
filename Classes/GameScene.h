#include "cocos2d.h"
#include "Box2D/Box2D.h"
//#include "chipmunk.h"
#include "SimpleAudioEngine.h"
#include "B2DebugDrawLayer.h"
#include "MyContactListener.h"
#include "Puck.h"
#include "Stick.h"
#include "GameWinScene.h"

class GameScene : public cocos2d::Layer, b2ContactListener
{
public:
	~GameScene();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init(); 

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::Scene* scene();
//	virtual void ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
//	virtual void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
//	virtual void ccTouchesMoved(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
//	virtual void ccTouchesCancelled(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    virtual bool onTouchBegan (cocos2d::Touch *touch, cocos2d::Event *event);
    virtual void onTouchMoved (cocos2d::Touch *touch, cocos2d::Event *event);
    virtual void onTouchEnded (cocos2d::Touch *touch, cocos2d::Event *event);
    virtual void onTouchCancelled (cocos2d::Touch *touch, cocos2d::Event *event);
    
	void menuCloseCallback(Object* pSender);
	void update(float dt);
	void createWorld();

	CREATE_FUNC(GameScene);

	MyContactListener *_contactListener;

private:

    b2World* world;
    cocos2d::Texture2D* m_pSpriteTexture; // weak ref

	b2ContactListener* _collisionListener;
	
	Puck* _puck;
	Stick* _stick;



	int GameStatus;
    bool _stickExist;
    int _cupBonus;
	//float kScaleX;
	int _iCups;
    
    LabelTTF* _ScoreLabel;
	SpriteBatchNode* _gameBatchNode;
    
    int _Score;
    void playerScore (int player);
    void timer(float t);
	void GameEnd(bool _win);
	void GameTimer();
	void resetGame(void);
    Point _startPoint;
	Point _endPoint;
    
private:
    int SCREEN_HEIGHT;
	int SCREEN_WIDTH;
    float kScale;
    
    int SCREEN_HEIGHT_DELTA;
	//b2Vec2 _startStickPos;
	float _startStickPosX;
	float _startStickPosY;
	float _endStickPosX;
	float _endStickPosY;
};


