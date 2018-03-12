#ifndef HELICOPTER_H
#define HELICOPTER_H

#include "Object.h"
#include "Rotor.h"
#include "Definitions.h"

class Helicopter : public Object{
			
public:
	Helicopter();
	bool PostInitialize();
	Object* Update(GAME_FLT, View*);
	void Draw(GAME_FLT, View*);
protected:
	Rotor* rotor;

};

#endif