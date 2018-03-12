#ifndef CARRIERFACTORY_H
#define CARRIERFACTORY_H

#include "ObjectFactory.h"
#include "Carrier.h"

class CarrierFactory : ObjectFactory{
			
public:
	virtual Object* create();
};

#endif