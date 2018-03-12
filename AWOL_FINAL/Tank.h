#ifndef TANK_H
#define TANK_H

#include "Object.h"
#include "Turret.h"
#include "Definitions.h"

class Tank : public Object{
			
public:
	Tank();
	bool PostInitialize();
	Object* Update(GAME_FLT, View*);
	void Draw(GAME_FLT, View*);
protected:
	Turret* turret;

};

#endif