#include"Definitions.h"
#include"GameSprite.h"
#include"ArtAssetLibrary.h"
#include"PhysicsAssetLibrary.h"
#include"GameAssetLibrary.h"
#include"Tent.h"

Tent::Tent(){
	id = "Tent";
}

Object* Tent::Update(GAME_FLT GameTime, View* view){

	return(NULL);

}

void Tent::Draw(GAME_FLT GameTime, View* view){

	//Convert Physics World to Render World
	GAME_VEC position;
	position.x = PW2RW(body->GetPosition().x);
	position.y = PW2RW(body->GetPosition().y);
	position.z = PW2RW(0.0f);
	GAME_FLT angle = body->GetAngle();

	//Draw Sprite in Render World
	sprite->Draw(0.0f, view, position, angle);

}
