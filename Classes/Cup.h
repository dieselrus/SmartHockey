#include "cocos2d.h"
#include "Box2D/Box2D.h"

using namespace cocos2d;

#pragma once
class Cup
{
public:
	Cup(Sprite* _sprite, int _maxPosY, int _minPosY, b2World* _world, float kScale);
	~Cup(void);
    
	b2Fixture* _cupFixture;
	b2FixtureDef _cupShapeDef;
	cocos2d::Texture2D* m_pSpriteTexture;
	int IntRand(int _max, int _min);
	b2FixtureDef getFixtureDef();
};

