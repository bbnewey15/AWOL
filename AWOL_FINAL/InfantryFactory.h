#ifndef INFANTRYFACTORY_H
#define INFANTRYFACTORY_H

#include "ObjectFactory.h"

class InfantryFactory : ObjectFactory{
			
public:
	virtual Object* create();
};

#endif