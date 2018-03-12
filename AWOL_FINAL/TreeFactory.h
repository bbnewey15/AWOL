#ifndef TREEFACTORY_H
#define TREEFACTORY_H

#include "ObjectFactory.h"
#include "Tree.h"

class TreeFactory : ObjectFactory{
			
public:
	virtual Object* create();
};

#endif