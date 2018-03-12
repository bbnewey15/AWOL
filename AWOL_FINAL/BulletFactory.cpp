#include "BulletFactory.h"
#include "Bullet.h"

Object* BulletFactory::create(){
	return((Object*)(new Bullet()));
}