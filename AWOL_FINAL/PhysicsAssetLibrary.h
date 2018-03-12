#ifndef PHYSICSASSETLIBRARY
#define PHYSICSASSETLIBRARY

#include<map>
#include<string>
#include "GamePhysics.h"

class PhysicsAssetLibrary{

public:
	PhysicsAssetLibrary();
	bool Initialize();
	bool IsInitialized();
	bool Insert(std::string name, std::string type, std::string shape, GAME_FLT density, GAME_FLT restitution, GAME_FLT angDamp, GAME_FLT linDamp, GAME_FLT angForce, GAME_FLT linForce);
	GamePhysics* Search(std::string);

private:
	std::map<std::string,GamePhysics*> library;

};

#endif