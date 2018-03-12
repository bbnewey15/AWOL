#include"Definitions.h"
#include"Infantry.h"
#include"GameAssetLibrary.h"

Infantry::Infantry(){
	id = "Infantry";
	IsSkull = false;
	IsPlayerFound = false;
	soundPlayed = false;
	tmpObject = NULL;
	health = 2;
	charge = 65;
	chargeTime = 65;
}

void Infantry::SetIsSkull(bool IsSkull){
	this->IsSkull = IsSkull;
}

bool Infantry::GetIsSkull(){
	return(IsSkull);
}

Object* Infantry::Update(GAME_FLT GameTime, View* view){
	didScore = false;

	//Get Player
	if(!IsPlayerFound){
		IsPlayerFound = GetPlayer(); //returns boolean 
	}
	//Charge Time for bullets
	if(charge<chargeTime){
		charge++;
	}
	//rObject = return object
	Object* rObject = NULL;
	if(!IsSkull){

		//get player position
		GAME_VEC playerPosConvv;
		playerPosConvv.x = PW2RW(tmpBody->GetPosition().x);
		playerPosConvv.y = PW2RW(tmpBody->GetPosition().y);
		playerPosConvv.z = PW2RW(0.0f);
		//get this position
		GAME_VEC thisPosConv;
		thisPosConv.x = PW2RW(body->GetPosition().x);
		thisPosConv.y = PW2RW(body->GetPosition().y);
		thisPosConv.z = PW2RW(0.0f);
		//Rotate the Infantry
		//body->SetAngularVelocity(body->GetAngularVelocity()-GetPhysics()->GetAngularForce());

		//Move the Carrier Backwards
		/*b2Vec2 force;
		force.x=-GetPhysics()->GetLinearForce()*cos(body->GetAngle()-3.14159f/2.0f);
		force.y=-GetPhysics()->GetLinearForce()*sin(body->GetAngle()-3.14159f/2.0f);
		body->ApplyForce(force,body->GetPosition());*/


		//always fixed on player
		GAME_FLT dy = playerPosConvv.y - thisPosConv.y;
		GAME_FLT dx = playerPosConvv.x - thisPosConv.x;
		GAME_FLT angToPlayer = atan2(dy,dx);  //atan2 is reverse (y,x)

		body->SetTransform(body->GetPosition(), angToPlayer + 3.14159f/2);
		GAME_FLT distance;
		if(IsPlayerFound){
			distance = sqrt(pow((thisPosConv.x - playerPosConvv.x), 2) + pow((thisPosConv.y - playerPosConvv.y), 2)); 
		}
		
		if( distance < 200 ){
			//Create and Fire Bullet!
			
			if(charge>=chargeTime){
				rObject = Fire();
			}
		}

	}
	else{ // if skull
		if(!soundPlayed){
			(sLibrary->Search("infDead"))->PlaySound();
			soundPlayed = true;
			didScore = true;
		}
		
	}

	return(rObject);
}

void Infantry::Draw(GAME_FLT GameTime, View* view){

	//Convert Physics World to Render World
	GAME_VEC position;
	position.x = PW2RW(body->GetPosition().x);
	position.y = PW2RW(body->GetPosition().y);
	position.z = PW2RW(0.0f);
	GAME_FLT angle = body->GetAngle();

	//Draw Sprite in Render World
	sprite->Draw(0.0f, view, position, angle);
}

bool Infantry::GetPlayer(){
	// find player in the physics world
	if(tmpObject != NULL && tmpObject->GetId() == "Player"){ 
		return true;
	}
	else{
		tmpBody = world->GetBodyList();
		tmpObject = (Object*)tmpBody->GetUserData();

		while(tmpObject->GetId() != "Player"){
			tmpBody = tmpBody->GetNext();
			tmpObject = (Object*)tmpBody->GetUserData();
		}
		return true;
	}
			
	
	
}

Object* Infantry::Fire(){

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