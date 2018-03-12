#ifndef BULLETFACTORY_H
#define BULLETFACTORY_H

#include "ObjectFactory.h"
#include "Bullet.h"

class BulletFactory : ObjectFactory{
			
public:
	virtual Object* create();
};

#endif