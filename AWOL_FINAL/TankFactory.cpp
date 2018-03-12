#include "TankFactory.h"
#include "Tank.h"

Object* TankFactory::create(){
	return((Object*)(new Tank()));
}