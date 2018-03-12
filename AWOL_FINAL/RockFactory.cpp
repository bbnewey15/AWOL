#include "RockFactory.h"
#include "Rock.h"

Object* RockFactory::create(){
	return((Object*)(new Rock()));
}