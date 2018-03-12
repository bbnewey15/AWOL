#include<iostream>
#include<Box2D/Box2D.h>
#include"Definitions.h"
#include"Infantry.h"
#include"Object.h"
#include"Carrier.h"
#include "Player.h"
#include "SoundLibrary.h"


class GameContactListener : public b2ContactListener{

public:

	void BeginContact(b2Contact* contact){}

	void EndContact(b2Contact* contact){}

	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold){ 

		//Handle pre-solve event 
		b2Body* bodyA = contact->GetFixtureA()->GetBody();
		b2Body* bodyB = contact->GetFixtureB()->GetBody();

		Object* objectA = (Object*)bodyA->GetUserData();
		Object* objectB = (Object*)bodyB->GetUserData();

		//=====================================
		//Handle Bullet vs Infantry collisions
		//=====================================

		//Check for desired collision
		if((objectA->GetId()).compare("Bullet")==0 && (objectB->GetId()).compare("Infantry")==0){
			
			if( (((Infantry*)objectB)->GetHealth()) == 1 ) {
				objectB->SetSprite("Skull");
				((Infantry*)objectB)->SetIsSkull(true); //if health < 1 
			}
			else { // decrement health by 1 and change to red
				objectB->SetSprite("Injured");
				((Infantry*)objectB)->SetHealth((((Infantry*)objectB)->GetHealth())-1);
			}
			objectA->SetIsDead(true);
		}

		//Check for opposite possibility
		if((objectB->GetId()).compare("Bullet")==0 && (objectA->GetId()).compare("Infantry")==0){
			
			if( (((Infantry*)objectA)->GetHealth()) == 1 ) {
				objectA->SetSprite("Skull");
				((Infantry*)objectA)->SetIsSkull(true); //if health < 1 
			}
			else {// decrement health by 1 and change to red
				objectA->SetSprite("Injured");
				((Infantry*)objectA)->SetHealth((((Infantry*)objectA)->GetHealth())-1);
			}
			objectB->SetIsDead(true);
		}
		//=====================================
		//Handle Bullet vs Carrier collisions
		//=====================================
		//Check for desired collision
		if((objectA->GetId()).compare("Bullet")==0 && (objectB->GetId()).compare("Carrier")==0){
			
			if( (((Carrier*)objectB)->GetHealth()) == 1 ) {
				objectB->SetSprite("Rubble");
				((Carrier*)objectB)->SetIsRubble(true); //if health < 1 
			}
			else { // decrement health by 1
				((Carrier*)objectB)->SetHealth((((Carrier*)objectB)->GetHealth())-1);
			}
			objectA->SetIsDead(true);
		}

		//Check for opposite possibility
		if((objectB->GetId()).compare("Bullet")==0 && (objectA->GetId()).compare("Carrier")==0){
			
			if( (((Carrier*)objectA)->GetHealth()) == 1 ) {
				objectA->SetSprite("Rubble");
				((Carrier*)objectA)->SetIsRubble(true); //if health < 1 
			}
			else {// decrement health by 1
				((Carrier*)objectA)->SetHealth((((Carrier*)objectA)->GetHealth())-1);
			}
			objectB->SetIsDead(true);
		}

		//=====================================
		//Handle Bullet vs Player collisions
		//=====================================
		//Check for desired collision
		if((objectA->GetId()).compare("Bullet")==0 && (objectB->GetId()).compare("Player")==0){
			
			if( (((Player*)objectB)->GetHealth()) == 1 ) {
				objectB->SetSprite("Rubble");
				((Player*)objectB)->SetIsRubble(true); //if health < 1 
			}
			else { // decrement health by 1
				((Player*)objectB)->SetHealth((((Player*)objectB)->GetHealth())-1);
			}
			objectA->SetIsDead(true);
		}

		//Check for opposite possibility
		if((objectB->GetId()).compare("Bullet")==0 && (objectA->GetId()).compare("Player")==0){
			
			if( (((Player*)objectA)->GetHealth()) == 1 ) {
				objectA->SetSprite("Rubble");
				((Player*)objectA)->SetIsRubble(true); //if health < 1 
			}
			else {// decrement health by 1
				((Player*)objectA)->SetHealth((((Player*)objectA)->GetHealth())-1);
			}
			objectB->SetIsDead(true);
		}

		//=====================================
		//Handle Helicopter vs Player collisions
		//=====================================
		//Check for desired collision
		if((objectA->GetId()).compare("Rotor")==0 && (objectB->GetId()).compare("Player")==0){
			((Player*)objectB)->SetIsHeliReached(true);
			
		}

		//Check for opposite possibility
		if((objectB->GetId()).compare("Rotor")==0 && (objectA->GetId()).compare("Player")==0){
			((Player*)objectA)->SetIsHeliReached(true);
			
		}

		//=====================================
		//Handle Bullet vs Tree collisions
		//=====================================

		//Check for desired collision
		if((objectA->GetId()).compare("Bullet")==0 && (objectB->GetId()).compare("Tree")==0){
			//objectB->SetSprite("Skull");
			//((Infantry*)objectB)->SetIsSkull(true);
			objectA->SetIsDead(true);
		}

		//Check for opposite possibility
		if((objectB->GetId()).compare("Bullet")==0 && (objectA->GetId()).compare("Tree")==0){
			//objectA->SetSprite("Skull");
			//((Infantry*)objectA)->SetIsSkull(true);
			objectB->SetIsDead(true);
		}


	}

	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse){}

};