// include the basic windows header file
#include <windows.h>
#include "Definitions.h"
#include <ctime>
#include "Game.h"
#include "log.h"


bool GenerateWindow(HINSTANCE hInstance, int nCmdShow, LPCSTR className, LPCSTR windowTitle, int x, int y,  int width, int height, HWND& hWnd);

// the WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

//Game engine
Game* game;


// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){

	//Provide access to terminal
    allocateStdIO();

	srand((unsigned)time(0));


	bool done = false;

	HWND hWnd;

	if(GenerateWindow(hInstance, nCmdShow, "Win32Window", "Main Game Window", 1, 1, SCREEN_WIDTH, SCREEN_HEIGHT, hWnd)){

		// this struct holds Windows event messages
		MSG msg;

		//Construct the Game Engine
		game = new Game();

		if(game->Initialize(hWnd,hInstance)){

			//main game loop
			while(!done){

				// wait for the next message in the queue, store the result in 'msg'
				while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
					// translate and dispatch to WindowProc()
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}

				// If the message is WM_QUIT, exit the while loop
				if(msg.message == WM_QUIT){
					done = true;
				}else{

					//Run the game
					done = game->Run();

				}

			}

		}

		//Clean-up
		delete game;

		// return this part of the WM_QUIT message to Windows
		return msg.wParam;

	}

	return 0;

}

bool GenerateWindow(HINSTANCE hInstance, int nCmdShow, LPCSTR className, LPCSTR windowTitle, int x, int y, int width, int height, HWND& hWnd){

	// this struct holds information for the window class
	WNDCLASSEX wc;

	// clear out the window class for use
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);  //Load an icon here
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = className;
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);

	// register the window class
	if(!RegisterClassEx(&wc)){
		return false;
	}

	// create the window and use the result as the handle
	hWnd = CreateWindowEx(NULL,className,  // name of the window class
		windowTitle,							// title of the window
		WS_OVERLAPPEDWINDOW | WS_SYSMENU | WS_MINIMIZEBOX,			// window style
		x,										// x-position of the window
		y,										// y-position of the window
		width,									// width of the window
		height,									// height of the window
		NULL,									// we have no parent window, NULL
		NULL,									// we aren't using menus, NULL
		hInstance,								// application handle
		NULL);									// used with multiple windows, NULL

	// display the window on the screen
	ShowWindow(hWnd, nCmdShow);

	return true;

}

// WindowProc - Handles input sent to the window
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	// sort through and find what code to run for the message given
	switch(message){
		// this message is read when the window is closed
	case WM_DESTROY:{
		PostQuitMessage(0);
		return 0;
					} break;
	}

	// Handle any messages the switch statement didn't
	return DefWindowProc (hWnd, message, wParam, lParam);
}

