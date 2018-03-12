#include "View.h"

View::View(){
	position.x=0.0f;
	position.y=0.0f;
	position.z=0.0f;

	center.x=0.0f;
	center.y=0.0f;
	center.z=0.0f;
	
	YRotVec.x = 0.0f;
	YRotVec.y = 0.0f;
	YRotVec.z = 0.0f;

	angle=0.0;

}

bool View::Initialize(GAME_FLT x, GAME_FLT y, GAME_FLT angle){
	center.x=x;
	center.y=y;
	this->angle = angle;

	return(true);
}

GAME_VEC View::GetPosition(){
	return(position);
}

GAME_VEC View::GetWindowCenter(){
	return(center);
}

GAME_FLT View::GetAngle(){
	return(angle);
}



void View::Update(GAME_FLT GameTime, InputDevice* iDevice){


	//Define a Angular Movement Magnitude
	GAME_FLT angMag = 0.02f;

	//Define a Linear Movement Magnitude
	GAME_FLT linMag = 3.0f;

	//Define a Unit Vector (y-axis up)
	GAME_VEC YUnitVec;
	YUnitVec.x=0.0;
	YUnitVec.y=-1.0;
	YUnitVec.z=0.0;

	//Construct a rotation matrix
	D3DXMATRIX Rotation;
	D3DXMatrixRotationZ(&Rotation,angle);

	//Transform the unit vector to the direction facing
	
	D3DXVec3TransformCoord(&YRotVec, &YUnitVec, &Rotation);
	
	//
	//Update View based on Input Evet
	//
	/*if(iDevice->IsLeftArrowPressed()){
		angle-=angMag;
	}

	if(iDevice->IsRightArrowPressed()){
		angle+=angMag;
	}*/

	if(iDevice->IsUpArrowPressed()){
		position=position+linMag*YRotVec;
	}

	if(iDevice->IsDownArrowPressed()){
		position=position-linMag*YRotVec;
	}

}

GAME_VEC View::SetPositionUp(){
	

	//Define a Linear Movement Magnitude
	GAME_FLT linMag = 1.0f;
	GAME_VEC oldP = position;
	position=position+linMag*YRotVec;

	return( position - oldP);
}

