#ifndef GRAPHICSDEVICE_H
#define GRAPHICSDEVICE_H

#include "Definitions.h"
#include <d3d9.h>


class GraphicsDevice{
		
public:
	GraphicsDevice();
	~GraphicsDevice();

	//Font and Text
	void PrintText(char*, int , int, int, DWORD);

	//Direct3D Function
	bool Initialize(HWND hwnd, bool windowed);
	void Clear(GAME_COLOR_RGB color);
	void Begin();
	void End();
	void Present();

	//Shorthand for IDirect3DDevice9 *device;
	GAME_DEVICE device;

private:
	GAME_GRAPHICS direct3d;
	LPD3DXFONT dxfont;

};

#endif