#include "PlayerFactory.h"
#include "Player.h"

Object* PlayerFactory::create(){
	return((Object*)(new Player()));
}