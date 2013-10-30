#include "Stick.h"
#include "Box2D/Box2D.h"

Stick::Stick(Sprite* _sprite, int PTM_RATIO, Point _startPos, Point _endPos, float _angle, b2World* _world, float kScale)
{
		float _posX = (_startPos.x + _endPos.x)/2/PTM_RATIO;
		float _posY = (_startPos.y + _endPos.y)/2/PTM_RATIO;
		double radians = atan2(_endPos.y - _startPos.y, _endPos.x - _startPos.x);
		float l = sqrt(fabs((_startPos.x - _endPos.x)/2/PTM_RATIO * (_startPos.x - _endPos.x)/2/PTM_RATIO + (_startPos.y - _endPos.y)/2/PTM_RATIO * (_startPos.y - _endPos.y)/2/PTM_RATIO)) ;

//        CCLOG("_startPos.x = %f, _startPos.y = %f", _startPos.x, _startPos.y);
//        CCLOG("_endPos.x = %f, _endPos.y = %f", _endPos.x, _endPos.y);
//        CCLOG("posX = %f, posY = %f, angle = %f, l = %f", _posX, _posY, radians, l);
    
		// Crete ball body
        //b2BodyDef _puckBodyDef;
        _stickBodyDef.type = b2_staticBody;
        //_stickBodyDef.position.Set(80/PTM_RATIO, 80/PTM_RATIO);
		_stickBodyDef.position.Set(_posX, _posY);
		//_stickBodyDef.position.Set(Pos.x, Pos.y);
		//_puckBodyDef.position.Set(240/PTM_RATIO, 400/PTM_RATIO);
		_stickBodyDef.angle = radians;
        _stickBodyDef.userData = _sprite;
		_sprite->setScaleX(l*2);
        //b2Body* _puckBody = _world->CreateBody(&_puckBodyDef);
		_stickBody = _world->CreateBody(&_stickBodyDef);
        
        b2EdgeShape stickBox;
		//stickBox.Set(b2Vec2((_startPos - 30)/PTM_RATIO, (_PosY)/PTM_RATIO), b2Vec2((_PosX + 30)/PTM_RATIO, (_PosY)/PTM_RATIO));
		//stickBox.Set(b2Vec2(_startPos.x/PTM_RATIO, _startPos.y/PTM_RATIO), b2Vec2(_endPos.x/PTM_RATIO, _endPos.y/PTM_RATIO));
		
		stickBox.Set(b2Vec2(-l, 0), b2Vec2(l, 0));
		_stickBody->CreateFixture(&stickBox,0);
}

b2Vec2 Stick::getBodyPos(){
	return _stickBodyDef.position;
}

b2Body* Stick::getBody(){
	if (_stickBody != NULL){
		return _stickBody;
	} else {
		return NULL;
	}
}

Stick::~Stick(void)
{
	delete _stickFixture;
}