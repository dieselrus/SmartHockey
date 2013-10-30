#include "Cup.h"


Cup::Cup(Sprite* _sprite, int _maxPosY, int _minPosY, b2World* _world, float kScale)
{
		//srand (time(NULL));
		// Create cup body
        _sprite->setScale(kScale);
		b2BodyDef cupBodyDef;
        cupBodyDef.type = b2_dynamicBody;
        cupBodyDef.position.Set(IntRand(12 * kScale, 3 * kScale), IntRand(_maxPosY * kScale, _minPosY * kScale));
		//cupBodyDef.position.Set(0,0);
        cupBodyDef.userData = _sprite;
        b2Body * cupBody = _world->CreateBody(&cupBodyDef);

		// Create cup shape
		b2Vec2 vertices[4];
		vertices[0].Set(-0.4f * kScale, -0.9f * kScale);
		vertices[1].Set(0.4f * kScale, -0.9f * kScale);
		vertices[2].Set(0.7f * kScale, 0.9f * kScale);
		vertices[3].Set(-0.7f * kScale, 0.9f * kScale);

		int32 count = 4;

        b2PolygonShape polyCup;
		polyCup.Set(vertices, count);

		// Create shape definition and add to body
        //b2FixtureDef cupShapeDef;
        _cupShapeDef.shape = &polyCup;
        _cupShapeDef.density = 1.0f;
        _cupShapeDef.friction = 0.f;
        _cupShapeDef.restitution = 1.0f;

		_cupFixture = cupBody->CreateFixture(&_cupShapeDef);
}


Cup::~Cup(void)
{
	delete _cupFixture;
}

// Произвольное число из интервала
int Cup::IntRand(int _max, int _min) 
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

b2FixtureDef Cup::getFixtureDef(){
	return _cupShapeDef;
}