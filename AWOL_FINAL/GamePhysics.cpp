#include "GamePhysics.h"
#include "Definitions.h"


GamePhysics::GamePhysics(){
	density = 1.0f;
	restitution = 1.0f;
	angularDamping = 0.0f;
	linearDamping = 0.0f;
	angularForce = 0.0f;
	linearForce = 0.0f;
}

GamePhysics::~GamePhysics(){
	//do nothing
}

bool GamePhysics::Initialize(std::string type, std::string shape, GAME_FLT density, GAME_FLT restitution, GAME_FLT angularDamping, GAME_FLT linearDamping, GAME_FLT angularForce, GAME_FLT linearForce){

	this->type = type;
	this->shape = shape;
	this->density = density;
	this->restitution = restitution;
	this->angularDamping = angularDamping;
	this->linearDamping = linearDamping;
	this->angularForce = angularForce;
	this->linearForce = linearForce;

	initialized = true;
	return(initialized);
}

bool GamePhysics::IsInitialized(){
	return(initialized);
}

GAME_FLT GamePhysics::GetDensity(){
	return(density);
}

GAME_FLT GamePhysics::GetRestitution(){
	return(restitution);
}

GAME_FLT GamePhysics::GetAngularDamping(){
	return(angularDamping);
}

GAME_FLT GamePhysics::GetLinearDamping(){
	return(linearDamping);
}

GAME_FLT GamePhysics::GetAngularForce(){
	return(angularForce);
}

GAME_FLT GamePhysics::GetLinearForce(){
	return(linearForce);
}

std::string GamePhysics::GetType(){
	return(type);
}

std::string GamePhysics::GetShape(){
	return(shape);
}