//
//  MenuLevelScene.h
//  HelloCpp
//
//  Created by diesel on 23.09.13.
//
//

#ifndef __MenuLevelScene__
#define __MenuLevelScene__

#include <iostream>
#include "cocos2d.h"

class MenuLevel : public cocos2d::Layer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::Scene* scene();
    
    // a selector callback
	void menuStartCallback(Object* pSender);
	void menuExitCallback(Object* pSender);
    
    //virtual void ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
	//virtual void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
	//virtual void ccTouchesMoved(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
	//virtual void ccTouchesCancelled(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    virtual bool onTouchBegan (cocos2d::Touch *touch, cocos2d::Event *event);
    virtual void onTouchMoved (cocos2d::Touch *touch, cocos2d::Event *event);
    virtual void onTouchEnded (cocos2d::Touch *touch, cocos2d::Event *event);
    virtual void onTouchCancelled (cocos2d::Touch *touch, cocos2d::Event *event);
    
    
    // implement the "static node()" method manually
    CREATE_FUNC(MenuLevel);
    void createMenuLevel(float _x, float _y, int _level);
    //void setkScale(float k);
    
private:
    int SCREEN_HEIGHT;
	int SCREEN_WIDTH;
    float kScale;
};
#endif /* defined(__MenuLevelScene__) */
