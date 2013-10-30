#include "cocos2d.h"
#include "Box2D/Box2D.h"

using namespace cocos2d;

#pragma once
class Puck
{
public:
	Puck(Sprite *_sprite, int PTM_RATIO, b2World* _world, float kScale);
	~Puck(void);
    
	b2Fixture* _puckFixture;
	b2FixtureDef _puckShapeDef;
	//cocos2d::CCTexture2D* m_pSpriteTexture;
	int IntRand(int _max, int _min);
	b2FixtureDef getFixtureDef();
	b2Body* _puckBody;
	b2BodyDef _puckBodyDef;
	void setApplyLinearImpulse(b2Vec2 force);
	b2Vec2 getBodyPos();
	void setVelocity(b2Vec2 force);
};