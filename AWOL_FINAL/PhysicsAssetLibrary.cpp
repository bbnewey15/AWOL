#include "PhysicsAssetLibrary.h"

PhysicsAssetLibrary::PhysicsAssetLibrary(){}

bool PhysicsAssetLibrary::Insert(std::string name, std::string type, std::string shape, GAME_FLT density, GAME_FLT restitution, GAME_FLT angDamp, GAME_FLT linDamp, GAME_FLT angForce, GAME_FLT linForce){
	GamePhysics* definition = new GamePhysics();
	if(definition->Initialize(type, shape, density, restitution, angDamp, linDamp, angForce, linForce)){
		library[name] = definition;
		return(true);
	}else{
		return(false);
	}
}

bool PhysicsAssetLibrary::Initialize(){
	return(true);
}


GamePhysics* PhysicsAssetLibrary::Search(std::string query){
	return((*library.find(query)).second);
}