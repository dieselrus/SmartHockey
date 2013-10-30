#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "cocos2d.h"

//#include "Box2D/Box2D.h"

//#include "chipmunk.h"

#include "SimpleAudioEngine.h"

class MainMenu : public cocos2d::Layer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::Scene* scene();
    
    // a selector callback
	void menuStartCallback(Object* pSender);
	void menuExitCallback(Object* pSender);

    // implement the "static node()" method manually
    CREATE_FUNC(MainMenu);
    
private:
    int SCREEN_HEIGHT;
	int SCREEN_WIDTH;
    float kScale;
};

#endif  // __MAINMENU_SCENE_H__