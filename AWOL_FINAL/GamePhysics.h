#ifndef GAMESPHYSICS_H
#define GAMESPHYSICS_H

#include "Definitions.h"
//#include "View.h"
class View;
class GamePhysics{
public:

	GamePhysics();
	~GamePhysics();

	bool Initialize(std::string type, std::string shape, GAME_FLT density, GAME_FLT restitution, GAME_FLT angularDamping, GAME_FLT linearDamping, GAME_FLT angularForce, GAME_FLT linearForce);
	bool IsInitialized();

	GAME_FLT GetDensity();
	GAME_FLT GetRestitution();
	GAME_FLT GetAngularDamping();
	GAME_FLT GetLinearDamping();
	GAME_FLT GetAngularForce();
	GAME_FLT GetLinearForce();
	std::string GetType();
	std::string GetShape();


private:

	GAME_FLT density;
	GAME_FLT restitution;
	GAME_FLT angularDamping;
	GAME_FLT linearDamping;
	GAME_FLT angularForce;
	GAME_FLT linearForce;
	std::string type;
	std::string shape;

	bool initialized;

};

#endif