#include"Definitions.h"
#include"GameSprite.h"
#include"ArtAssetLibrary.h"
#include"PhysicsAssetLibrary.h"
#include"GameAssetLibrary.h"
#include"Tank.h"

Tank::Tank(){
	id = "Tank";
	turret = NULL;

}

bool Tank::PostInitialize(){

	if(turret==NULL){

		turret = new Turret();
		turret->Initialize("Turret", iDevice, objects, gLibrary, aLibrary, pLibrary,sLibrary, world, 
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

Object* Tank::Update(GAME_FLT GameTime, View* view){

	//Rotate the Tank
	//body->SetAngularVelocity(body->GetAngularVelocity()-GetPhysics()->GetAngularForce());

	//Move the Tank Linearly
	/*b2Vec2 force;
	force.x=GetPhysics()->GetLinearForce()*cos(body->GetAngle()-3.14159f/2.0f);
	force.y=GetPhysics()->GetLinearForce()*sin(body->GetAngle()-3.14159f/2.0f);
	body->ApplyForce(force,body->GetPosition());*/

	//Update Turret Component
	turret->Update(GameTime, view);

	return(NULL);

}

void Tank::Draw(GAME_FLT GameTime, View* view){

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
