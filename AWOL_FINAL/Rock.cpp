#include"Definitions.h"
#include"Rock.h"

Rock::Rock(){
	id = "Rock";
}

Object* Rock::Update(GAME_FLT GameTime, View* view){
	
	////Force Scaling Coefficients (in Physics World)
	//GAME_FLT angularDampening = 0.15f;
	//GAME_FLT linearDampening = 0.08f;
	//GAME_FLT forceScalar = 0.2f;

	////Apply friction to AngularVelocity;
	//GAME_FLT currAngularVelocity = body->GetAngularVelocity();
	//currAngularVelocity += (-0.1f*currAngularVelocity);
	//body->SetAngularVelocity(currAngularVelocity);

	////Apply friction to LinearVelocity
	//b2Vec2 currLinearVelocity = body->GetLinearVelocity();
	//currLinearVelocity += (-0.1f*currLinearVelocity);
	//body->SetLinearVelocity(currLinearVelocity);

	//Do nothing
	return(NULL);

}


void Rock::Draw(GAME_FLT GameTime, View* view){

	//Convert Physics World to Render World
	GAME_VEC position;
	position.x = PW2RW(body->GetPosition().x);
	position.y = PW2RW(body->GetPosition().y);
	position.z = PW2RW(0.0f);
	GAME_FLT angle = body->GetAngle();

	//Draw Sprite in Render World
	sprite->Draw(0.0f, view, position, angle);

}
