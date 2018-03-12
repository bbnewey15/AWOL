#include<iostream>
#include<string>
#include"Definitions.h"
#include"Player.h"
#include"Bullet.h"
#include"GameAssetLibrary.h"

//Forward declare
class ArtAssetLibrary;
class PhysicsAssetLibrary;

Player::Player(){
	//charge = 25;
	//chargeTime = 25;
	id = "Player";
	turret = NULL;
	adj_screen_height = -(SCREEN_HEIGHT/2); //300 right now
	health = 150;
	IsRubble = false;
	isHelicopterReached = false;


}

bool Player::PostInitialize(){

	if(turret==NULL){

		turret = new PlayerTurret();
		turret->Initialize("PlayerTurret", iDevice, objects, gLibrary, aLibrary, pLibrary,sLibrary, world, 
						PW2RW(body->GetPosition().x), PW2RW(body->GetPosition().y),body->GetAngle()-1.0f);

		//
		//Define RevoluteJoint
		//
		b2RevoluteJointDef jd;
		jd.bodyA = body;
		jd.bodyB = turret->GetBody();
		jd.localAnchorA = b2Vec2(0.0f,0.0f);
		jd.localAnchorB = b2Vec2(0.0f,0.08f);

		//Add joint to physics world
		world->CreateJoint(&jd);

	}

	return(true);
}

Object* Player::Update(GAME_FLT GameTime, View* view){


	if(!IsRubble){
		//Respond to Inputs
		if(iDevice->IsAPressed()){
			body->SetAngularVelocity(body->GetAngularVelocity()-GetPhysics()->GetAngularForce());
		}

		if(iDevice->IsDPressed()){
			body->SetAngularVelocity(body->GetAngularVelocity()+GetPhysics()->GetAngularForce());	
		}

		if(iDevice->IsWPressed()){
			float angle = body->GetAngle();
			b2Vec2 force;
			force.x=GetPhysics()->GetLinearForce()*cos(angle-3.14159f/2.0f);
			force.y=GetPhysics()->GetLinearForce()*sin(angle-3.14159f/2.0f);
			body->ApplyForce(force,body->GetPosition());
		}

		if(iDevice->IsSPressed()){
			float angle = body->GetAngle();
			b2Vec2 force;
			force.x=GetPhysics()->GetLinearForce()*cos(angle+3.14159f/2.0f);
			force.y=GetPhysics()->GetLinearForce()*sin(angle+3.14159f/2.0f);
			body->ApplyForce(force,body->GetPosition());
		}

		b2Vec2 pos1 = body->GetPosition();
		GAME_VEC pos12;
		pos12.x = PW2RW(pos1.x);
		pos12.y = PW2RW(pos1.y);
		pos12.z = 0.0f;
		GAME_VEC dP;
		if( ( pos12.y - 300 ) < adj_screen_height ){
			//returns the screen adjustment
			dP = view->SetPositionUp();
			adj_screen_height += dP.y;
		}

	}

	Object* rObject = NULL;
	//update Turret
	if(turret!=NULL){
		rObject = turret->Update(GameTime, view);
	}
	
	return(rObject);

}




void Player::Draw(GAME_FLT GameTime, View* view){

	//Convert Physics World to Render World
	GAME_VEC position;
	position.x = PW2RW(body->GetPosition().x);
	position.y = PW2RW(body->GetPosition().y);
	position.z = PW2RW(0.0f);
	GAME_FLT angle = body->GetAngle();

	//Draw Sprite in Render World
	sprite->Draw(0.0f, view, position, angle);

	if(turret){
		turret->Draw(GameTime, view);
	}
}

void Player::SetIsRubble(bool IsRubble){
	this->IsRubble = IsRubble;
}

bool Player::GetIsHeliReached(){
	return(isHelicopterReached);
}
void Player::SetIsHeliReached(bool isReached){

	this->isHelicopterReached = isReached;
}