#include"Definitions.h"
#include"GameSprite.h"
#include"ArtAssetLibrary.h"
#include"PhysicsAssetLibrary.h"
#include"GameAssetLibrary.h"
#include"Tree.h"

Tree::Tree(){
	id = "Tree";
}

Object* Tree::Update(GAME_FLT GameTime, View* view){

	return(NULL);

}

void Tree::Draw(GAME_FLT GameTime, View* view){

	//Convert Physics World to Render World
	GAME_VEC position;
	position.x = PW2RW(body->GetPosition().x);
	position.y = PW2RW(body->GetPosition().y);
	position.z = PW2RW(0.0f);
	GAME_FLT angle = body->GetAngle();

	//Draw Sprite in Render World
	sprite->Draw(0.0f, view, position, angle);

}
