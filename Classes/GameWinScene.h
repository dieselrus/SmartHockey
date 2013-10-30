//
//  GameWinScene.h
//  HelloCpp
//
//  Created by admin on 20.10.13.
//
//

#ifndef __HelloCpp__GameWinScene__
#define __HelloCpp__GameWinScene__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

class GameWinScene : public cocos2d::Layer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
//    GameWinScene(int _cup, int _time, int _score);
//    ~GameWinScene();
    
    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::Scene* scene();
    
    
    
    // implement the "static node()" method manually
    CREATE_FUNC(GameWinScene);
    
private:
    //SpriteBatchNode *_gameBatchNode;
    void createScoreBoard(int _cup, int _time, int _score);
    // a selector callback
	void menuReloadCallback(Object* pSender);
	void menuNextCallback(Object* pSender);
    
    int SCREEN_HEIGHT;
	int SCREEN_WIDTH;
    float kScaleX;
};
#endif /* defined(__HelloCpp__GameWinScene__) */
