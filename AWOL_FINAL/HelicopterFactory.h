#ifndef HELICOPTERFACTORY_H
#define HELICOPTERFACTORY_H

#include "ObjectFactory.h"
#include "Helicopter.h"

class HelicopterFactory : ObjectFactory{
			
public:
	virtual Object* create();
};

#endif