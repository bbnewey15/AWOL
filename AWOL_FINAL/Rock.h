#ifndef ROCK_H
#define ROCK_H

#include "Object.h"
#include "Definitions.h"

class Rock : public Object{
			
public:
	Rock();
	Object* Update(GAME_FLT, View*);
	void Draw(GAME_FLT, View*);
private:
	GAME_FLT delta;

};

#endif