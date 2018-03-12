#include "CarrierFactory.h"
#include "Carrier.h"

Object* CarrierFactory::create(){
	return((Object*)(new Carrier()));
}