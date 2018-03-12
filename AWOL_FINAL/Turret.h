#ifndef TURRET_H
#define TURRET_H

#include "Object.h"
#include "Definitions.h"

class Turret : public Object{
			
public:
	Turret();
	Object* Update(GAME_FLT, View*);
	void Draw(GAME_FLT, View*);
private:

};

#endif