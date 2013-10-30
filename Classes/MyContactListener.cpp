#include "MyContactListener.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

MyContactListener::MyContactListener() : _contacts() {
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/board.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/gate.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/cup.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/hit.wav");
}
 
MyContactListener::~MyContactListener() {
}
 
void MyContactListener::BeginContact(b2Contact* contact) {
    // We need to copy out the data because the b2Contact passed in
    // is reused.
    MyContact myContact = { contact->GetFixtureA(), contact->GetFixtureB() };
	_contacts.push_back(myContact);
	
	b2Body *bodyA = contact->GetFixtureA()->GetBody();
    b2Body *bodyB = contact->GetFixtureB()->GetBody();

	if(bodyA->GetUserData() != NULL && bodyB->GetUserData() != NULL){
		Sprite *spriteA = (Sprite *) bodyA->GetUserData();
        Sprite *spriteB = (Sprite *) bodyB->GetUserData();

		// Puch & Board
		if(spriteA->getTag() == 2 && spriteB->getTag() == 1){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/board.wav");
		} 

		if(spriteA->getTag() == 1 && spriteB->getTag() == 2){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/board.wav");
		} 
		
		// Puch & Gate
		if(spriteA->getTag() == 1 && spriteB->getTag() == 4){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/gate.wav");
		}

		if(spriteA->getTag() == 4 && spriteB->getTag() == 1){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/gate.wav");
		}

		// Puch & Cup
		if(spriteA->getTag() == 1 && spriteB->getTag() == 3){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/cup.wav");
		}

		if(spriteA->getTag() == 3 && spriteB->getTag() == 1){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/cup.wav");
		}

		// Goal
		if(spriteA->getTag() == 1 && spriteB->getTag() == 5){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/cup.wav");
		}

		if(spriteA->getTag() == 5 && spriteB->getTag() == 1){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/cup.wav");
		}

		// hit
		if(spriteA->getTag() == 1 && spriteB->getTag() == 6){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/hit.wav");
		}

		if(spriteA->getTag() == 6 && spriteB->getTag() == 1){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/hit.wav");
		}
	}
}
 
void MyContactListener::EndContact(b2Contact* contact) {
	
    MyContact myContact = { contact->GetFixtureA(), contact->GetFixtureB() };
    std::vector<MyContact>::iterator pos;
    pos = std::find(_contacts.begin(), _contacts.end(), myContact);
    if (pos != _contacts.end()) {
        _contacts.erase(pos);
    }
	
}
 
void MyContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
		b2Body *bodyA = contact->GetFixtureA()->GetBody();
        b2Body *bodyB = contact->GetFixtureB()->GetBody();
        if (bodyA->GetUserData() != NULL && bodyB->GetUserData() != NULL) {
            Sprite *spriteA = (Sprite *) bodyA->GetUserData();
            Sprite *spriteB = (Sprite *) bodyB->GetUserData();
 
            //Sprite A = ball, Sprite B = Cup
			if (spriteA->getTag() == 3 || spriteB->getTag() == 3) {
				contact->SetEnabled(false);
            }
        }
}
 
void MyContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {
		b2Body *bodyA = contact->GetFixtureA()->GetBody();
        b2Body *bodyB = contact->GetFixtureB()->GetBody();
        if (bodyA->GetUserData() != NULL && bodyB->GetUserData() != NULL) {
            Sprite *spriteA = (Sprite *) bodyA->GetUserData();
            Sprite *spriteB = (Sprite *) bodyB->GetUserData();
 
            //Sprite A = ball, Sprite B = Stick
			if (spriteA->getTag() == 1 && spriteB->getTag() == 6) {
				
            }
			//Sprite B = ball, Sprite A = Stick
			if (spriteA->getTag() == 6 && spriteB->getTag() == 1) {
				
            }
        }
}
