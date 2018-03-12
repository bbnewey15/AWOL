#ifndef TANKFACTORY_H
#define TANKFACTORY_H

#include "ObjectFactory.h"
#include "Tank.h"

class TankFactory : ObjectFactory{
			
public:
	virtual Object* create();
};

#endif