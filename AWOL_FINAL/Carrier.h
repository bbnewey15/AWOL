#ifndef CARRIER_H
#define CARRIER_H

#include "Object.h"
#include "Definitions.h"

class Carrier : public Object{
			
public:
	Carrier();
	Object* Update(GAME_FLT, View*);
	void Draw(GAME_FLT, View*);

	void SetIsRubble(bool);
private:
	bool IsRubble;
	bool soundPlayed;
};

#endif