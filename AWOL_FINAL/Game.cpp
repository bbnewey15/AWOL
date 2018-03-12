#include <fstream>
#include <vector>
#include "Game.h"
//#include "GameFunctions.h"
#include "tinyxml.h"
#include "tinystr.h"
#include <sstream>



Game::Game():gravity(RW2PW(0),RW2PW(0)){
	gDevice=NULL;
	iDevice=NULL;
	aLibrary=NULL;
	pLibrary=NULL;
	gLibrary=NULL;
	sDevice=NULL;
	mManager = NULL;
	world = NULL;
	playerObject = NULL;
	gameTime = 0.0f;
	stepTime = 0.0f;

	score = 0;
}

Game::~Game(){

	//Destroy All Game Objects
	for(int i=0;i<(int)objects.size();i++){
		delete objects[i];
	}

	//Destroy the Physics World
	if(world){
		delete world;
		world = NULL;
	}

	//Destroy the Asset Libraries
	if(aLibrary){
		delete aLibrary;
		aLibrary = NULL;
	}

	if(pLibrary){
		delete pLibrary;
		pLibrary = NULL;
	}

	if(gLibrary){
		delete gLibrary;
		gLibrary = NULL;
	}

	//Destory the Devices
	if(gDevice){
		delete gDevice;
		gDevice = NULL;
	}

	if(iDevice){
		delete iDevice;
		iDevice = NULL;
	}

	if(sDevice){
		delete sDevice;
		sDevice = NULL;
	}

	if(mManager){
		delete mManager;
		mManager = NULL;
	}


}

bool Game::Initialize(HWND hWnd, HINSTANCE hInstance){

	

	//Initialize Game Members
	gameTime = 0.0f;

	//Size of numerical integration step
	stepTime = 0.1f;  

	//Construct the Graphics Device
	gDevice = new GraphicsDevice();
	if(!gDevice->Initialize(hWnd, true)){
		return false;
	}

	sDevice = new SoundDevice();
	if(!sDevice->Initialize(hWnd)){
		return false;
	}

	//Construct the Input Device
	iDevice = new InputDevice();
	if(!iDevice->Initialize(hInstance,hWnd)){
		return false;
	}

	//Construct Art Asset Library
	aLibrary = new ArtAssetLibrary();
	if(!aLibrary->Initialize(gDevice)){
		return false;
	}

	//Construct Physics Asset Library
	pLibrary = new PhysicsAssetLibrary();
	if(!pLibrary->Initialize()){
		return false;
	}

	//Construct Game Asset Library
	gLibrary = new GameAssetLibrary();
	if(!gLibrary->Initialize()){
		return false;
	}
	sLibrary = new SoundLibrary();
	if(!sLibrary->Initialize(sDevice->device)){
		return false;
	}

	//not working
	mManager = new MusicManager();
	if(!mManager->Initialize(sLibrary)){ //sDevice->device)){
		return false;
	}

	// this song is not working for whatever reason!
	(sLibrary->Search("my10am"))->PlaySound();



	//Construct the Camera
	view = new View();
	if(!view->Initialize(400.0,300.0, 0.0f)){
		return false;
	}

	//Construct the Physics World;
	world = new b2World(gravity);

	//Load GameAssets
	if(!LoadLevelFromXML("./Config/level.xml")){
		return false;
	}


	//Set-up the Contact Listener
	world->SetContactListener(&gcl);
	
	//Full Initialized Game
	return true;

}

bool Game::LoadLevelFromXML(const char* path){

	//======================================
	// Note: this function is largely based
	// on Jeff Long's implementation of a
	// LoadLevel() function for Homework #1
	//======================================
	Object* tmp;

	//Perform XML Parsing as a demo
	TiXmlDocument levelConfig(path);

	if(!levelConfig.LoadFile()) 
		return(false);

	TiXmlHandle hDoc(&levelConfig);
	TiXmlElement* pRoot;
	TiXmlElement* pParm;
	TiXmlElement* pInner;
	
	//Set up the Level
	pRoot= levelConfig.FirstChildElement("Level");

	//Should always have a level
	if (!pRoot) 
		return(false);

	//======================================
	//Set-up the Game Assets from Factories
	//=====================================
	pParm = pRoot->FirstChildElement("Resources")->FirstChildElement("Factories");
	
	//Should always have a factory
	if(!pParm)
			return(false);

	pInner = pParm->FirstChildElement("Factory");
	for(pInner; pInner; pInner=pInner->NextSiblingElement("Factory")){
		//Insert this type of GameAsset into the GameAssetLibrary (Note:
		//these are selected form a hardcoded list
		gLibrary->Insert(pInner->Attribute("type"));
	}


	//==============================
	//Set-up the Art Assets
	//==============================
	pParm = pRoot->FirstChildElement("Resources")->FirstChildElement("Sprites");
	
	//Should always have a factory
	if(!pParm)
			return(false);

	pInner = pParm->FirstChildElement("Sprite");
	for(pInner; pInner; pInner=pInner->NextSiblingElement("Sprite")){
		GAME_INT width=0, height=0;
		const char* name = pInner->Attribute("name");
		const char* file = pInner->Attribute("file");
		pInner->QueryIntAttribute("width",&width);
		pInner->QueryIntAttribute("height",&height);

		//Insert this type of Art Asset into the PhysicsAssetLibrary
		aLibrary->Insert(name,file,width,height);	
	}
	
	//==============================
	//Set-up the Physics Definitions
	//==============================
	pParm = pRoot->FirstChildElement("Resources")->FirstChildElement("PhysicsDefinitions");
	
	//Should always have a factory
	if(!pParm)
			return(false);

	pInner = pParm->FirstChildElement("Definition");
	for(pInner; pInner; pInner=pInner->NextSiblingElement("Definition")){
		GAME_FLT density=0.0f, restitution=0.0f, angDamp=0.0f, linDamp=0.0f, angForce=0.0f, linForce=0.0f;
		const char* name = pInner->Attribute("name");
		const char* type = pInner->Attribute("type");
		const char* shape = pInner->Attribute("shape");
		pInner->QueryFloatAttribute("density",&density);
		pInner->QueryFloatAttribute("restitution",&restitution);
		pInner->QueryFloatAttribute("angDamp",&angDamp);
		pInner->QueryFloatAttribute("linDamp",&linDamp);
		pInner->QueryFloatAttribute("angForce",&angForce);
		pInner->QueryFloatAttribute("linForce",&linForce);

		//Insert this type of Physics Definition into the PhysicsAssetLibrary
		pLibrary->Insert(name,type,shape,density,restitution,angDamp,linDamp,angForce,linForce);	
	}

	//==============================
	//Set-up the Level Layout
	//==============================
	pParm = pRoot->FirstChildElement("Layout");
	
	//Should always have a factory
	if(!pParm)
			return(false);

	pInner = pParm->FirstChildElement("GameAsset");
	for(pInner; pInner; pInner=pInner->NextSiblingElement("GameAsset")){
	
		//Get GameAsset Name
		const char *pKey=pInner->Attribute("name");

		//Load GameAsset Params
		GAME_FLT x=0.0f, y=0.0f, angle=0.0f;
		pInner->QueryFloatAttribute("x", &x);
		pInner->QueryFloatAttribute("y", &y);
		pInner->QueryFloatAttribute("angle", &angle);

		//Construct and load object into game space
		tmp = gLibrary->Search(pKey);
		tmp->Initialize(pKey,iDevice,&objects,gLibrary,aLibrary,pLibrary,sLibrary,world,x,y,angle);
		tmp->PostInitialize();
		objects.push_back(tmp);
	}

	//Completed without failure
	return(true);

}


bool Game::Run(){

	//Update Physics and Game World
	Update(gameTime);

	//Update Render World
	Draw(gameTime);

	//Update Time
	gameTime+=stepTime;

	if(timeleft < 0 || playerHealth <= 1 || (((Player*)playerObject)->GetIsHeliReached()) ){
		return(true);
	}
	else
		return(false);
}

void Game::Update(float gameTime){

	std::vector<Object*>::iterator oiter;

	//Update timer
	timeleft = 90 - (t.GetMilliseconds()/1000);

	
	
	
	//=============================
	//Handle  Input Events
	//=============================
	if(iDevice){
		iDevice->Update();
	}

	//=============================
	//Update the Game World View
	//=============================
	view->Update(gameTime,iDevice);

	//=============================
	//Update Pysics World
	//=============================
	world->Step(1.0f/60.0f, 6, 2);

	//=============================
	//Update Game World
	//=============================

	//Update each object
	std::vector<Object*> newObjects;
	for(oiter=objects.begin();oiter!=objects.end();oiter++){
		if((*oiter) && (*oiter)->IsInitialized()){
			Object* newObject = (*oiter)->Update(gameTime, view);
			if(newObject!=NULL){
				newObjects.push_back(newObject);
			}
			// Update Player Health
			if((*oiter)->GetId() == "Player"){
				playerObject = (*oiter);
				playerHealth = (*oiter)->GetHealth();
				
			}
			if((*oiter)->GetAddScore()){
				score += 10;
			}
		
		}
	}

	//Add newly created objects into Game World
	for(int i=0;i<(int)newObjects.size();i++){
		objects.push_back(newObjects[i]);
	}

	//Garbage collect "dead" objects
	for(oiter=objects.begin();oiter!=objects.end();){
		if( (*oiter)->GetIsDead()){
			delete (*oiter);
			oiter = objects.erase(oiter);
		}else{
			oiter++;
		}
	}

	//Music Update
	mManager->Update();

	
}

void Game::Draw(float gameTime){

	//Clear the screen to the given color
	gDevice->Clear(D3DCOLOR_XRGB(230, 240, 170));

	//Set-up the blittin gprocess
	gDevice->Begin();

	//Render each game element
	for(int i=0;i<(int)objects.size();i++){
		if(objects[i] && objects[i]->IsInitialized()){
			objects[i]->Draw(gameTime,view);
		}
	}

	
	//all this mess to display text
	char scoreString[20] = "Score: ";
	std::stringstream ss;
	ss << scoreString << score;
	//scoreString = ss.str();
	char *cstr = new char[(ss.str()).length() + 1];
	strcpy(cstr, (ss.str()).c_str());
	gDevice->PrintText(cstr, 25, 10, 10, D3DCOLOR_RGBA(255,0,0,255));
	delete [] cstr;

	//Timer
	char timeString[20] = "Timer: ";
	std::stringstream ss2;
	ss2 << timeString << timeleft;
	char *cstr2 = new char[(ss2.str()).length() + 1];
	strcpy(cstr2, (ss2.str()).c_str());
	gDevice->PrintText(cstr2, 25, 650, 10, D3DCOLOR_RGBA(255,0,0,255));
	delete [] cstr2;

	//PlayerHealth
	char healthString[20] = "Health: ";
	std::stringstream ss3;
	ss3 << healthString << playerHealth;
	char *cstr3 = new char[(ss3.str()).length() + 1];
	strcpy(cstr3, (ss3.str()).c_str());
	gDevice->PrintText(cstr3, 25, 10, 530, D3DCOLOR_RGBA(255,0,0,255));
	delete [] cstr3;

	if(((Player*)playerObject)->GetIsHeliReached()){
		char winString[20] = "YOU WIN";
		gDevice->PrintText(winString, 380, 290, 530, D3DCOLOR_RGBA(255,0,0,255));


	}

	//Shut-down the blitting process
	gDevice->End();
	
	//Blit the data
	gDevice->Present();
	
}

int Game::GetScore(){
	return(score);
}
void Game::SetScore(int score){
	this->score = score;
}
