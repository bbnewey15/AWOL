#ifndef PLAYERFACTORY_H
#define PLAYERFACTORY_H

#include "ObjectFactory.h"
#include "Player.h"

class PlayerFactory : ObjectFactory{
			
public:
	virtual Object* create();
};

#endif