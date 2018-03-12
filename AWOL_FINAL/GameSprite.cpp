#include "InputDevice.h"
#include "GameSprite.h"
#include "Definitions.h"

GameSprite::GameSprite(){
	//Sprite Parameters
	width = 0.0f;
	height = 0.0f;
	initialized=false;
}

GameSprite::~GameSprite(){

	if(sprite){
		sprite->Release();
		sprite=NULL;
	}

	if(tex){
		tex->Release();
		tex=NULL;
	}
}

GAME_FLT GameSprite::GetHeight(){
	return(height);
}

GAME_FLT GameSprite::GetWidth(){
	return(width);
}

bool GameSprite::Initialize(GAME_DEVICE device, GAME_STR file, GAME_INT width, GAME_INT height){

	this->width=(GAME_FLT)width;
	this->height=(GAME_FLT)height;

	//Same functionality as D3DXCreateTextureFromFile EXCEPT width and height are maually entered
	if(!SUCCEEDED(D3DXCreateTextureFromFileEx(device,file.c_str(),width,height,D3DX_DEFAULT, 0, D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &tex))){
			std::string s = "There was an issue creating the texture. Make sure the requested image is available. Requested image: " + file;
			MessageBox(NULL, s.c_str(), NULL, NULL);
			return(false);
	}

	//Attempt to create the sprite
	if(!SUCCEEDED(D3DXCreateSprite(device, &sprite))){
		MessageBox(NULL, "There was an issue creating the sprite", NULL, NULL);
	}
	initialized = true;
	return(true);
}

bool GameSprite::IsInitialized(){
	return(initialized);
}

void GameSprite::Draw(GAME_FLT GameTime, View* view, GAME_VEC Position, GAME_FLT Angle){
	
	if(sprite && tex){

		//Unpack the view
		GAME_VEC CameraPosition = view->GetPosition();
		GAME_FLT CameraAngle = view->GetAngle();
		GAME_VEC WindowCenter = view->GetWindowCenter();

		//Start Rendering
		sprite->Begin(D3DXSPRITE_ALPHABLEND);

		//Compute Center of Object
		D3DXMATRIX mat;
		D3DXMatrixRotationZ(&mat,-CameraAngle); //Because view space is reflected about the y-axis

		GAME_VEC DiffFromCamera;
		DiffFromCamera = Position-CameraPosition;

		//Rotate Relative to Camera
		GAME_VEC RelPosition;
		D3DXVec3TransformCoord(&RelPosition, &DiffFromCamera, &mat);

		//Transform the Sprite
		D3DXMATRIX MatTransform;
		D3DXMatrixTransformation2D(&MatTransform, NULL, NULL, NULL,  &D3DXVECTOR2(width/2, height/2), Angle-CameraAngle, &D3DXVECTOR2(WindowCenter.x+RelPosition.x-width/2, WindowCenter.y+RelPosition.y-height/2));
		sprite->SetTransform(&MatTransform);

		//Draw the sprite
		sprite->Draw(tex, NULL, NULL, NULL, D3DCOLOR_ARGB(255,255,255,255));

		//Finish Rendering
		sprite->End();
	}

}