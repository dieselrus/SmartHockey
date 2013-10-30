#include "Gate.h"


Gate::Gate(Sprite* _sprite, int PTM_RATIO, float _PosX, float _PosY, b2World* _world, float kScale)
{
    CCLOG("_PosX = %f, _PosY = %f", _PosX, _PosY);
    //srand (time(NULL));
	// Create cup body
    //_sprite->setScale(kScale);
	b2BodyDef _gateBodyDef;
    _gateBodyDef.type = b2_staticBody;
    _gateBodyDef.position.Set(_PosX/PTM_RATIO * kScale, _PosY/PTM_RATIO * kScale);
	//cupBodyDef.position.Set(0,0);
    _gateBodyDef.userData = _sprite;
    b2Body * _gateBody = _world->CreateBody(&_gateBodyDef);

    b2PolygonShape polyGate;
	// Create shape definition and add to body
    //b2FixtureDef cupShapeDef;
    _gateShapeDef.shape = &polyGate;
    _gateShapeDef.density = 1.0f;
    _gateShapeDef.friction = 0.f;
    _gateShapeDef.restitution = 1.0f;

    float scale = _sprite->getScaleX();

    b2Vec2 verticesGate[8];
		
	verticesGate[0].Set(29.0f * scale/PTM_RATIO, 11.0f/PTM_RATIO);
	verticesGate[1].Set(24.0f * scale/PTM_RATIO, 16.0f/PTM_RATIO);
	verticesGate[2].Set(-24.0f * scale/PTM_RATIO, 16.0f/PTM_RATIO);
	verticesGate[3].Set(-29.0f * scale/PTM_RATIO, 10.0f/PTM_RATIO);
	verticesGate[4].Set(-32.0f * scale/PTM_RATIO, 3.0f/PTM_RATIO);
	verticesGate[5].Set(-29.0f * scale/PTM_RATIO, 2.0f/PTM_RATIO);
	verticesGate[6].Set(28.0f * scale/PTM_RATIO, 2.0f/PTM_RATIO);
	verticesGate[7].Set(31.0f * scale/PTM_RATIO, 3.0f/PTM_RATIO);

	int32 countGate = 8;
	polyGate.Set(verticesGate, countGate);
	_gateFixture = _gateBody->CreateFixture(&_gateShapeDef);

		
	verticesGate[0].Set(24.0f * scale/PTM_RATIO, -16.0f/PTM_RATIO);
	verticesGate[1].Set(26.0f * scale/PTM_RATIO, -16.0f/PTM_RATIO);
	verticesGate[2].Set(31.0f * scale/PTM_RATIO, 3.0f/PTM_RATIO);
	verticesGate[3].Set(28.0f * scale/PTM_RATIO, 2.0f/PTM_RATIO);

    countGate = 4;
	polyGate.Set(verticesGate, countGate);
	_gateFixture = _gateBody->CreateFixture(&_gateShapeDef);

	verticesGate[0].Set(-24.0f * scale/PTM_RATIO, -16.0f/PTM_RATIO);
	verticesGate[1].Set(-29.0f * scale/PTM_RATIO, 2.0f/PTM_RATIO);
	verticesGate[2].Set(-32.0f * scale/PTM_RATIO, 3.0f/PTM_RATIO);
	verticesGate[3].Set(-26.0f * scale/PTM_RATIO, -16.0f/PTM_RATIO);

	polyGate.Set(verticesGate, countGate);
	_gateFixture = _gateBody->CreateFixture(&_gateShapeDef);

//================== SENSOR GOAL ======================================================		
	Sprite* spSensorGoal = new Sprite();
	spSensorGoal->setTag(5);
    spSensorGoal->setScale(kScale);
	// Define the ground body.
	b2BodyDef sensorBodyDef;
	//sensorBodyDef.position.Set(0, 0); // bottom-left corner
	sensorBodyDef.userData = spSensorGoal;
	// The body is also added to the world.
	b2Body* sensorBody = _world->CreateBody(&sensorBodyDef);

    // Define the ground box shape.
	b2EdgeShape sensorBox;

	sensorBox.Set(b2Vec2((_PosX - 30)/PTM_RATIO * kScale, _PosY/PTM_RATIO * kScale), b2Vec2((_PosX + 30)/PTM_RATIO * kScale, _PosY/PTM_RATIO * kScale));
    sensorBody->CreateFixture(&sensorBox,0);
}


Gate::~Gate(void)
{
	delete _gateFixture;
}
