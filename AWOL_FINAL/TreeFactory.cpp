#include "TreeFactory.h"
#include "Tree.h"

Object* TreeFactory::create(){
	return((Object*)(new Tree()));
}