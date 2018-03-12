#include"Definitions.h"
#include"PlayerTurret.h"
#include"GameAssetLibrary.h"

PlayerTurret::PlayerTurret(){
	id = "PlayerTurret";
	charge = 25;
	chargeTime = 25;
}

Object* PlayerTurret::Update(GAME_FLT GameTime, View* view){

	if(charge<chargeTime){
		charge++;
	}

	//Force Scaling Coefficients (in Physics World)
	GAME_FLT forceAngular = GetPhysics()->GetAngularForce();


	//Respond to Inputs
	//body->SetAngularVelocity(body->GetAngularVelocity()-forceAngular);
	if(iDevice->IsLeftArrowPressed()){
		body->SetAngularVelocity(body->GetAngularVelocity()-forceAngular);
	}

	if(iDevice->IsRightArrowPressed()){
		body->SetAngularVelocity(body->GetAngularVelocity()+forceAngular);
	}


	//Create and Fire Bullet!
	Object* rObject = NULL;
	if((iDevice->IsSpacePressed()) & (charge>=chargeTime)){
		rObject = Fire();
	}


	return(rObject);

}

void PlayerTurret::Draw(GAME_FLT GameTime, View* view){

	//Convert Physics World to Render World
	GAME_VEC position;
	position.x = PW2RW(body->GetPosition().x);
	position.y = PW2RW(body->GetPosition().y);
	position.z = PW2RW(0.0f);
	GAME_FLT angle = body->GetAngle();

	//Draw Sprite in Render World
	sprite->Draw(0.0f, view, position, angle);

}

Object* PlayerTurret::Fire(){

	Object* rObject = NULL;

	//Reset Player's charge
	charge=0;

	//
	//Do calculations to place Bullet at end of gun barrel
	//

	//Figure out x,y
	GAME_VEC bProject;
	bProject.x=0.0;
	bProject.y=-1.0;
	bProject.z=0.0;

	D3DXMATRIX bMat;
	D3DXMatrixRotationZ(&bMat,body->GetAngle());

	GAME_VEC bGradient;
	bGradient.x = 0.0f;
	bGradient.y = 1.0f;
	D3DXVec3TransformCoord(&bGradient, &bProject, &bMat);

	GAME_FLT offset = sprite->GetHeight()/2.0f;
	if(sprite->GetWidth()/2.0f>offset){
		offset = sprite->GetWidth();
	}

	GAME_VEC InitPosition;
	InitPosition.x = bGradient.x*offset + PW2RW(body->GetPosition().x);
	InitPosition.y = bGradient.y*offset + PW2RW(body->GetPosition().y);

	//Construct the bullet
	std::string key("Bullet");
	Object* bullet = gLibrary->Search(key);


	//Initialize the bullet
	if(bullet->Initialize(key, iDevice, objects, gLibrary, aLibrary, pLibrary,sLibrary, world, InitPosition.x, InitPosition.y, body->GetAngle())){

		//Build force imparted in the Bullet
		b2Vec2 force;
		force.x=-bullet->GetPhysics()->GetLinearForce()*cos(body->GetAngle()+3.14159f/2.0f);
		force.y=-bullet->GetPhysics()->GetLinearForce()*sin(body->GetAngle()+3.14159f/2.0f);

		//Apply force to Bullet
		bullet->GetBody()->ApplyForce(force,body->GetPosition());

		//All done...add the object to the game space
		rObject = bullet;
	}

	return(rObject);
}

