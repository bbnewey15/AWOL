//Example input handling: adapted from http://www.rastertek.com/dx10tut13.html

#include "InputDevice.h"

// The following macro allows you to test if
// a key is currently pressed
#define KEYDOWN(name, key) (name[key] & 0x80)

InputDevice::InputDevice(){
	directInput = NULL;
	keyboard = NULL;
}

InputDevice::~InputDevice(){

	if(directInput){
		directInput->Release();
		directInput = NULL;
	}

	if(keyboard){
		keyboard->Unacquire();
		keyboard->Release();
		keyboard = NULL;
	}

}

//Direct3D Function
bool InputDevice::Initialize(HINSTANCE hinst, HWND hwnd){//, int screenWidth, int screenHeight){

	//This function call will initialize the interface to Direct Input. Once you have a Direct Input object you can initialize other input devices.
	// Initialize the main direct input interface.
	if(!SUCCEEDED(DirectInput8Create(hinst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, NULL))){
		return false;
	}

	//The first input device we will initialize will be the keyboard.
	// Initialize the direct input interface for the keyboard.
	if(!SUCCEEDED(directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL))){
		return false;
	}

	// Set the data format.  In this case since it is a keyboard we can use the predefined data format.
	if(!SUCCEEDED(keyboard->SetDataFormat(&c_dfDIKeyboard))){
		return false;
	}

	//Setting the cooperative level of the keyboard is important in both what it does and
	//how you use the device from that point forward. In this case we will set it to not 
	//share with other programs (DISCL_EXCLUSIVE). This way if you press a key only your
	//application can see that input and no other application will have access to it. However
	//if you want other applications to have access to keyboard input while your program is 
	//running you can set it to non-exclusive (DISCL_NONEXCLUSIVE). Now the print screen key
	//works again and other running applications can be controlled by the keyboard and so forth.
	//Just remember that if it is non-exclusive and you are running in a windowed mode then you
	//will need to check for when the device loses focus and when it re-gains that focus so it
	//can re-acquire the device for use again. This focus loss generally happens when other
	//windows become the main focus over your window or your window is minimized.

	// Set the cooperative level of the keyboard to not share with other programs.
	if(!SUCCEEDED(keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE))){
		return false;
	}

    //Once they keyboard is setup we then call Acquire to finally get access to the keyboard 
	//for use from this point forward.
	// Now acquire the keyboard.
	if(!SUCCEEDED(keyboard->Acquire())){
		return false;
	}


	return true;

}

bool InputDevice::Update(){

	if(!ReadKeyboard()){
		return false;
	}

	return true;

}


bool InputDevice::ReadKeyboard(){

	// Read the keyboard device.
	HRESULT result = keyboard->GetDeviceState(sizeof(keyboardState), (LPVOID)&keyboardState);
	
	if(!SUCCEEDED(result)){

		// If the keyboard lost focus or was not acquired then try to get control back.
		if((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED)){
			keyboard->Acquire();
		}else{
			return false;
		}
	}
		
	return true;

}


bool InputDevice::IsLeftArrowPressed(){

	// Do a bitwise and on the keyboard state to check if the escape key is currently being pressed.
	if(KEYDOWN(keyboardState, DIK_LEFT)){
		return true;
	}

	return false;

}

bool InputDevice::IsRightArrowPressed(){

	// Do a bitwise and on the keyboard state to check if the escape key is currently being pressed.
	if(KEYDOWN(keyboardState, DIK_RIGHT)){
		return true;
	}

	return false;

}


bool InputDevice::IsUpArrowPressed(){
	// Do a bitwise and on the keyboard state to check if the escape key is currently being pressed.
	if(KEYDOWN(keyboardState, DIK_UP)){
		return true;
	}

	return false;
}

bool InputDevice::IsDownArrowPressed(){
	// Do a bitwise and on the keyboard state to check if the escape key is currently being pressed.
	if(KEYDOWN(keyboardState, DIK_DOWN)){
		return true;
	}

	return false;
}


bool InputDevice::IsWPressed(){
	// Do a bitwise and on the keyboard state to check if the escape key is currently being pressed.
	if(KEYDOWN(keyboardState, DIK_W)){
		return true;
	}
	return false;
}

bool InputDevice::IsAPressed(){
		// Do a bitwise and on the keyboard state to check if the escape key is currently being pressed.
	if(KEYDOWN(keyboardState, DIK_A)){
		return true;
	}
	return false;
}

bool InputDevice::IsSPressed(){
	// Do a bitwise and on the keyboard state to check if the escape key is currently being pressed.
	if(KEYDOWN(keyboardState, DIK_S)){
		return true;
	}
	return false;
}

bool InputDevice::IsDPressed(){
	// Do a bitwise and on the keyboard state to check if the escape key is currently being pressed.
	if(KEYDOWN(keyboardState, DIK_D)){
		return true;
	}
	return false;
}

bool InputDevice::IsSpacePressed(){
	// Do a bitwise and on the keyboard state to check if the escape key is currently being pressed.
	if(KEYDOWN(keyboardState, DIK_SPACE)){
		return true;
	}
	return false;
}