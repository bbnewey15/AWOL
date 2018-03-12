#include<iostream>
#include"Definitions.h"
#include"Bullet.h"

Bullet::Bullet(){
	lifeSpan = 0;
	maxLifeSpan = 10;
	id = "Bullet";
	soundPlayed = false;
}

Object* Bullet::Update(GAME_FLT GameTime, View* view){

	if(!soundPlayed){
		(sLibrary->Search("bulletSound"))->PlaySound();
		soundPlayed = true;
	}

	if(lifeSpan<maxLifeSpan){
		lifeSpan++;
	}else{
		isDead=true;

	}

	return(NULL);

}


void Bullet::Draw(GAME_FLT GameTime, View* view){

	//Convert Physics World to Render World
	GAME_VEC position;
	position.x = PW2RW(body->GetPosition().x);
	position.y = PW2RW(body->GetPosition().y);
	position.z = PW2RW(0.0f);
	GAME_FLT angle = body->GetAngle();

	//Draw Sprite in Render World
	sprite->Draw(0.0f, view, position, angle);

}
