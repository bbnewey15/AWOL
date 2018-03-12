#ifndef TENT_H
#define TENT_H

#include "Object.h"
#include "Definitions.h"

class Tent : public Object{
			
public:
	Tent();
	Object* Update(GAME_FLT, View*);
	void Draw(GAME_FLT, View*);

};

#endif