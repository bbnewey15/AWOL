#include"Definitions.h"
#include"Turret.h"

Turret::Turret(){
	id = "Turret";
}

Object* Turret::Update(GAME_FLT GameTime, View* view){

	//Force Scaling Coefficients (in Physics World)
	GAME_FLT forceAngular = 0.1f;

	//Respond to Inputs
	body->SetAngularVelocity(body->GetAngularVelocity()-forceAngular);

	return(NULL);

}

void Turret::Draw(GAME_FLT GameTime, View* view){

	//Convert Physics World to Render World
	GAME_VEC position;
	position.x = PW2RW(body->GetPosition().x);
	position.y = PW2RW(body->GetPosition().y);
	position.z = PW2RW(0.0f);
	GAME_FLT angle = body->GetAngle();

	//Draw Sprite in Render World
	sprite->Draw(0.0f, view, position, angle);

}
