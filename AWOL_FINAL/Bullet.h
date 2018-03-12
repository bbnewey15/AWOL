#ifndef BULLET_H
#define BULLET_H

#include "Object.h"
#include "Definitions.h"

class Bullet : public Object{
			
public:
	Bullet();
	~Bullet();
	Object* Update(GAME_FLT, View*);
	void Draw(GAME_FLT, View*);
private:
	GAME_FLT delta;
	GAME_INT lifeSpan;
	GAME_INT maxLifeSpan;
	bool soundPlayed;

};

#endif