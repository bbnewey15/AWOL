#include "HelicopterFactory.h"
#include "Helicopter.h"

Object* HelicopterFactory::create(){
	return((Object*)(new Helicopter()));
}