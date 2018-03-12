#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define DIRECTINPUT_VERSION 0x0800

#include <vector>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include <string>

//DirectX Library Defns
typedef LPDIRECT3DDEVICE9 GAME_DEVICE;
typedef LPDIRECT3D9 GAME_GRAPHICS;

//Basic Quantities
typedef D3DXMATRIX	GAME_MAT;
typedef D3DXVECTOR3 GAME_VEC;
typedef float       GAME_FLT;
typedef int			GAME_INT;
typedef std::string GAME_STR;

//DirectX Sprite Defns
typedef D3DCOLOR GAME_COLOR_RGB;
typedef	LPDIRECT3DTEXTURE9 GAME_TEXTURE;
typedef	LPD3DXSPRITE GAME_SPRITE;

//DirectX Event Defns
typedef IDirectInput8* GAME_INPUT_PTR;
typedef IDirectInputDevice8* GAME_KEYBOARD_PTR;

//Conversion Functions
const float fPRV = 100.0f;
inline float PW2RW(float x){return x*fPRV;}
inline float RW2PW(float x){return x/fPRV;}
inline float RW2PW(int x){return (float)x/fPRV;}

//Screen Adjustments
const int SCREEN_HEIGHT = 600;
const int SCREEN_WIDTH = 800;

#endif