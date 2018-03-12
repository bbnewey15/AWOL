#ifndef ROTOR_H
#define ROTOR_H

#include "Object.h"
#include "Definitions.h"

class Rotor : public Object{
			
public:
	Rotor();
	Object* Update(GAME_FLT, View*);
	void Draw(GAME_FLT, View*);
private:

};

#endif