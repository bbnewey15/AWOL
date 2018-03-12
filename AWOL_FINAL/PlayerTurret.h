#ifndef PLAYERTURRET_H
#define PLAYERTURRET_H

#include "Object.h"
#include "Definitions.h"



class PlayerTurret : public Object{
			
public:
	PlayerTurret();
	Object* Update(GAME_FLT, View*);
	void Draw(GAME_FLT, View*);
	Object* Fire();
private:
	GAME_INT charge;
	GAME_INT chargeTime;
};

#endif