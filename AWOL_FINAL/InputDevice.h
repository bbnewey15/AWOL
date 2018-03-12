#ifndef INPUTDEVICE_H
#define INPUTDEVICE_H

///////////////////////////////
// PRE-PROCESSING DIRECTIVES //
///////////////////////////////
//#define DIRECTINPUT_VERSION 0x0800

#include "Definitions.h"

class InputDevice{
		
public:
	InputDevice();
	~InputDevice();

	//Direct3D Function
	bool Initialize(HINSTANCE hinst, HWND hwnd);
	bool Update();
		
	bool IsLeftArrowPressed();
	bool IsRightArrowPressed();

	bool IsUpArrowPressed();
	bool IsDownArrowPressed();

	bool IsWPressed();
	bool IsAPressed();
	bool IsSPressed();
	bool IsDPressed();

	bool IsSpacePressed();

private:

	bool ReadKeyboard();
	void ProcessInput();

	GAME_INPUT_PTR directInput;
	GAME_KEYBOARD_PTR keyboard;

	unsigned char keyboardState[256];
};

#endif