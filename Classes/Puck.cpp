#include "Puck.h"

Puck::Puck(Sprite* _sprite, int PTM_RATIO, b2World* _world, float kScale)
{
        _sprite->setScale(kScale);
        // Crete ball body
        //b2BodyDef _puckBodyDef;
        _puckBodyDef.type = b2_dynamicBody;
        //ballBodyDef.position.Set(80/PTM_RATIO, 80/PTM_RATIO);
		//_puckBodyDef.position.Set(IntRand(14, 2), 2);
        _puckBodyDef.position.Set(IntRand(14 * kScale, 2 * kScale), IntRand(20 * kScale, 2 * kScale));
		//_puckBodyDef.position.Set(240/PTM_RATIO, 400/PTM_RATIO);
        _puckBodyDef.userData = _sprite;
		_puckBodyDef.bullet = true;
        //b2Body* _puckBody = _world->CreateBody(&_puckBodyDef);
		_puckBody = _world->CreateBody(&_puckBodyDef);
        
        // Create circle shape
        b2CircleShape circle;
        circle.m_radius = 16.0/PTM_RATIO * kScale;
        
        // Create shape definition and add to body
        b2FixtureDef _puckShapeDef;
        _puckShapeDef.shape = &circle;
        _puckShapeDef.density = 1.0f;
        _puckShapeDef.friction = 0.f;
        _puckShapeDef.restitution = 1.0f;
        _puckFixture = _puckBody->CreateFixture(&_puckShapeDef);
		_puckShapeDef.isSensor = true;
		
}

// Произвольное число из интервала
int Puck::IntRand(int _max, int _min) 
{ 
	//char str[11];
	//str += "";
	//sprintf(str, "%d", _max);
	//CCLog(str);

	//int c = _min + rand() % _max;
	int c = _min + double(rand()) / RAND_MAX * (_max - _min); 
	if(c >= _max ){
		IntRand(_max, _min);
	}
	
	//char str[11];
	//sprintf(str, "%d", c);
	//CCLog(str);
	return c;
}

void Puck::setApplyLinearImpulse(b2Vec2 force){
	_puckBody->ApplyLinearImpulse(force, _puckBodyDef.position);
	//_puckBody->ApplyLinearImpulse(force, _puckBody->GetPosition());
}

void Puck::setVelocity(b2Vec2 force){
	_puckBody->SetLinearVelocity(force);
	//_puckBody->ApplyLinearImpulse(force, _puckBody->GetPosition());
}

b2Vec2 Puck::getBodyPos(){
	return _puckBodyDef.position;
}

Puck::~Puck(void)
{
	delete _puckFixture;
}