#include "GraphicsDevice.h"


GraphicsDevice::GraphicsDevice(){
	//Constructor

	
}

GraphicsDevice::~GraphicsDevice(){

	//Releasing all graphics resources

	if(device){
		device->Release();
		device = NULL;
	}

	if(direct3d){
		direct3d->Release();
		direct3d = NULL;
	}

}

bool GraphicsDevice::Initialize(HWND hwnd, bool windowed){
	
	//Create the Direct 3D Pointer
	direct3d = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS presentationParams;
	ZeroMemory(&presentationParams, sizeof(presentationParams));
	presentationParams.Windowed = windowed;
	presentationParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
	presentationParams.hDeviceWindow = hwnd;

	//Create the device
	if(!SUCCEEDED(direct3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, D3DCREATE_MIXED_VERTEXPROCESSING, &presentationParams, &device))){
		return(false);
	}
	
	D3DXCreateFont(device,    // the D3D Device
                   35,    // font height
                   0,    // default font width
                   FW_BOLD,    // font weight
                   1,    // not using MipLevels
                   false,    // italic font
                   DEFAULT_CHARSET,    // default character set
                   OUT_DEFAULT_PRECIS,    // default OutputPrecision,
                   DEFAULT_QUALITY,    // default Quality
                   DEFAULT_PITCH | FF_DONTCARE,    // default pitch and family
                   "Arial",    // use Facename Arial
                   &dxfont);    // the font object


	return true;
}

// h ttp://cboard.cprogramming.com/game-programming/116614-directx-%7C-drawing-text.html
void GraphicsDevice::PrintText(char* str, int size, int x, int y, DWORD color){
    static RECT textbox;
    SetRect(&textbox, x, y, SCREEN_WIDTH, SCREEN_HEIGHT);
    

    dxfont->DrawTextA(NULL,
                      str,
                      strlen(str),
                      &textbox,
                      DT_LEFT | DT_TOP,
                      color);
}

void GraphicsDevice::Clear(D3DCOLOR color){

	//2nd param is set to "NULL" so that it clears the entire back buffer
	device->Clear(0,NULL,D3DCLEAR_TARGET, color, 1.0f, 0);

}

void GraphicsDevice::Begin(){
	device->BeginScene();
}

void GraphicsDevice::End(){
	device->EndScene();
}

void GraphicsDevice::Present(){
	//Present our scene to the window
	device->Present(NULL,NULL,NULL,NULL);
}