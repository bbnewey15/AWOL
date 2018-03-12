#ifndef PLAYER_H
#define PLAYER_H

#include "Object.h"
#include "PlayerTurret.h"
#include "Definitions.h"

class Player : public Object{
			
public:
	Player();
	bool PostInitialize();
	Object* Update(GAME_FLT, View*);
	void Draw(GAME_FLT, View*);
	//Object* Fire();
	void SetIsRubble(bool);
	bool GetIsHeliReached();
	void SetIsHeliReached(bool);
private:

	//GAME_INT charge;
	//GAME_INT chargeTime;
	GAME_FLT delta;
	GAME_FLT adj_screen_height;
	bool IsRubble;
	bool isHelicopterReached;
protected:
	PlayerTurret* turret;

};

#endif