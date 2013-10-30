#include "cocos2d.h"
#include "Box2D/Box2D.h"

using namespace cocos2d;

#pragma once
class Gate
{
public:
	Gate(Sprite* _sprite, int PTM_RATIO, float _PosX, float _PosY, b2World* _world, float kScale);
	~Gate(void);
    
	b2Fixture* _gateFixture;
	b2FixtureDef _gateShapeDef;
	//b2FixtureDef getFixtureDef();
};