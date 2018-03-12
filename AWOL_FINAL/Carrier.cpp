#include"Definitions.h"
#include"Carrier.h"

Carrier::Carrier(){
	id = "Carrier";
	health = 3;
	IsRubble = false;
	soundPlayed = false;
}

Object* Carrier::Update(GAME_FLT GameTime, View* view){
	didScore = false;
	if(!IsRubble){

	}
	else{
		if(!soundPlayed){
			(sLibrary->Search("carrierDead"))->PlaySound();
			soundPlayed = true;
			didScore = true;
		}
	}
	return(NULL);

}

void Carrier::Draw(GAME_FLT GameTime, View* view){

	//Convert Physics World to Render World
	GAME_VEC position;
	position.x = PW2RW(body->GetPosition().x);
	position.y = PW2RW(body->GetPosition().y);
	position.z = PW2RW(0.0f);
	GAME_FLT angle = body->GetAngle();

	//Draw Sprite in Render World
	sprite->Draw(0.0f, view, position, angle);

}

void Carrier::SetIsRubble(bool IsRubble){
	this->IsRubble = IsRubble;
}