#ifndef VIEW_H
#define VIEW_H

#include "Definitions.h"
#include "InputDevice.h"



class View {
			
public:
	View();
	void Update(GAME_FLT, InputDevice*);
	bool Initialize(GAME_FLT, GAME_FLT, GAME_FLT);
	GAME_VEC GetPosition();
	GAME_VEC GetWindowCenter();
	GAME_FLT GetAngle();

	GAME_VEC SetPositionUp();


private:

	GAME_VEC YRotVec;
	GAME_VEC position;
	GAME_VEC center;
	GAME_FLT angle;
};

#endif