#include "TentFactory.h"
#include "Tent.h"

Object* TentFactory::create(){
	return((Object*)(new Tent()));
}