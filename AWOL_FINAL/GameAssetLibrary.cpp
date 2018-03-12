#include "GameAssetLibrary.h"
#include "TankFactory.h"
#include "CarrierFactory.h"
#include "InfantryFactory.h"
#include "RockFactory.h"
#include "BulletFactory.h"
#include "PlayerFactory.h"
#include "TreeFactory.h"
#include "HelicopterFactory.h"
#include "TentFactory.h"

GameAssetLibrary::GameAssetLibrary(){
}
	
void GameAssetLibrary::Insert(std::string type){
	
	if(type == "Tank"){
		library["Tank"] = (ObjectFactory*)(new TankFactory());
	}

	if(type == "Carrier"){
		library["Carrier"] = (ObjectFactory*)(new CarrierFactory());
	}

	if(type == "Infantry"){
		library["Infantry"] = (ObjectFactory*)(new InfantryFactory());
	}

	if(type == "Rock"){
		library["Rock"] = (ObjectFactory*)(new RockFactory());
	}

	if(type == "Bullet"){
		library["Bullet"] = (ObjectFactory*)(new BulletFactory());
	}

	if(type == "Player"){
		library["Player"] = (ObjectFactory*)(new PlayerFactory());
	}

	if(type == "Tree"){
		library["Tree"] = (ObjectFactory*)(new TreeFactory());
	}
	if(type == "Tent"){
		library["Tent"] = (ObjectFactory*)(new TentFactory());
	}

	if(type == "Helicopter"){
		library["Helicopter"] = (ObjectFactory*)(new HelicopterFactory());
	}

}

bool GameAssetLibrary::Initialize(){


	return(true);
}

Object* GameAssetLibrary::Search(std::string query){
	return(((*library.find(query)).second)->create());
}