#include "InfantryFactory.h"
#include "Infantry.h"

Object* InfantryFactory::create(){
	return((Object*)(new Infantry()));
}