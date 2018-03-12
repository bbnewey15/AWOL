#include<iostream>
#include "Object.h"
#include "GameAssetLibrary.h"
#include "ArtAssetLibrary.h"
#include "PhysicsAssetLibrary.h"
#include <Box2D/Box2D.h>

Object::Object(){
	id="Object";
	gLibrary = NULL;
	aLibrary = NULL;
	pLibrary = NULL;
	sLibrary = NULL;
	physics = NULL;
	world = NULL;
	body = NULL;
	initialized = false;
	isDead = false;
	didScore = false;
}

Object::~Object(){

	//Reset all Game World pointers to NULL
	gLibrary = NULL;
	aLibrary = NULL;
	pLibrary = NULL;
	physics = NULL;
	sLibrary = NULL;

	//Reset all Physics World pointers to NULL
	if(body){
		world->DestroyBody(body);
		body=NULL;
	}
	world = NULL;

}

std::string Object::GetId(){
	return(id);
}

bool Object::GetIsDead(){
	return(isDead);
}

b2Body* Object::GetBody(){
	return(body);
}

GamePhysics* Object::GetPhysics(){
	return(physics);
}

void Object::SetIsDead(bool isDead){
	this->isDead=isDead;
}

void Object::SetSprite(std::string spriteName){
	this->sprite = aLibrary->Search(spriteName);
}

bool Object::GetAddScore(){
	return(didScore);
}

GAME_INT Object::GetHealth(){
	return(health);
}

void Object::SetHealth(GAME_INT h){
	this->health = h;
}

bool Object::Initialize(std::string key, InputDevice* iDevice, std::vector<Object*>* objects, 
					GameAssetLibrary* gLibrary, ArtAssetLibrary* aLibrary, PhysicsAssetLibrary* pLibrary, SoundLibrary* sLibrary, b2World* world, GAME_FLT x, GAME_FLT y, GAME_FLT angle){


	//================================
	//Initialize Members
	//================================
	this->iDevice = iDevice;
	this->objects = objects;
	this->gLibrary = gLibrary;
	this->aLibrary = aLibrary;
	this->pLibrary = pLibrary;
	this->sLibrary = sLibrary;
	this->sprite = aLibrary->Search(key);
	this->physics = pLibrary->Search(key);
	this->world = world;

	//==============================================
	//Create this object's physics (body) definition
	//==============================================
	b2BodyDef bd;

	//
	//Determine body type (dynamic or static)
	//
	if(physics->GetType().compare("dynamic")==0){
		bd.type = b2_dynamicBody; 
	}else{
		bd.type = b2_staticBody;  
	}
	
	//
	//Set the body's orientation (position and angle)
	//
	bd.position.Set(RW2PW(x),RW2PW(y));
	bd.angle = angle;
	bd.userData = this;

	//==============================================
	//Register this body with the physics system
	//==============================================
	body = world->CreateBody(&bd);
	
	//==============================================
	//Create the physics properties of this body to match the Art/Game requirements
	//==============================================
	
	b2PolygonShape polyShape;	
	polyShape.SetAsBox(RW2PW((float)sprite->GetWidth()/2.0f),RW2PW((float)sprite->GetHeight()/2.0f));		

	b2CircleShape circleShape;
	circleShape.m_radius = RW2PW((float)sprite->GetWidth()/2.0f);

	//Define the shape (either poly or circle)
	b2FixtureDef fixtureDef;
	if(physics->GetShape().compare("poly")==0){
		fixtureDef.shape = &polyShape;
	}else{
		fixtureDef.shape = &circleShape;
	}

	//==============================================
	//Set physical properties of the fixture
	//==============================================
	fixtureDef.density = physics->GetDensity();  
	fixtureDef.restitution = physics->GetRestitution(); 

	body->SetAngularDamping(physics->GetAngularDamping());
	body->SetLinearDamping(physics->GetLinearDamping());

	//==============================================
	//Provide this object to the physics world
	//==============================================
	body->SetUserData(this);

	//==============================================
	//Register the physics properties with physics system
	//==============================================
	body->CreateFixture(&fixtureDef);

	initialized=true;
	return(initialized);
}

bool Object::PostInitialize(){
	return(true);
}

bool Object::IsInitialized(){
	return(initialized);
}
