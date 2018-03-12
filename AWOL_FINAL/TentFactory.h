#ifndef TENTFACTORY_H
#define TENTFACTORY_H

#include "ObjectFactory.h"
#include "Tent.h"

class TentFactory : ObjectFactory{
			
public:
	virtual Object* create();
};

#endif