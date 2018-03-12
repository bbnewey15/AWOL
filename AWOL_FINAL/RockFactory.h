#ifndef ROCKFACTORY_H
#define ROCKFACTORY_H

#include "ObjectFactory.h"
#include "Rock.h"

class RockFactory : ObjectFactory{
			
public:
	virtual Object* create();
};

#endif