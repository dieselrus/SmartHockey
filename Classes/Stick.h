#include "cocos2d.h"
#include "Box2D/Box2D.h"

using namespace cocos2d;

#pragma once
class Stick
{
public:
	Stick(Sprite* _sprite, int PTM_RATIO, Point _startPos, Point _endPos, float _angle, b2World* _world, float kScale);
	~Stick(void);
    
	b2Fixture* _stickFixture;

	b2Body* _stickBody;
	b2BodyDef _stickBodyDef;
	b2Vec2 getBodyPos();
	b2Body* getBody();
};