#ifndef INFANTRY_H
#define INFANTRY_H

#include "Object.h"
#include "Definitions.h"
#include <vector>

class Infantry : public Object{
			
public:
	Infantry();
	Object* Update(GAME_FLT, View*);
	void Draw(GAME_FLT, View*);
	void SetIsSkull(bool);
	bool GetIsSkull();
	Object* Fire();
	
	bool GetPlayer();
private:
	bool IsSkull;
	bool IsPlayerFound;
	bool soundPlayed;
	b2Body* tmpBody;
	Object* tmpObject;
	GAME_INT charge;
	GAME_INT chargeTime;

};

#endif