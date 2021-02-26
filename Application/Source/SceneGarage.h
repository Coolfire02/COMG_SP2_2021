#ifndef SCENE_GARAGE_H
#define SCENE_GARAGE_H

#include <map>

#include "Scene.h"
#include "Camera.h"
#include "Game.h"
#include "Inventory.h"
#include "MeshBuilder.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Interactions.h"

#include "EntityManager.h"
#include "ButtonManager.h"
#include "InteractionManager.h"
#include "MeshHandler.h"

//Entities
#include "NPC.h"
#include "CustomEntity.h"
#include "WorldObject.h"

/*
* Scene Setup
* In Init, 
Change Scene Name Accordingly
Init the Player Entity

TODOs:
Migrate Most Interaction Handling to Interaction Manager
*/

class SceneGarage : public Scene
{
	enum INTERACTION_TYPE {
		TEST,
		INTERACTION_COUNT,
	};

private:

	Camera camera;
	Camera camera2;

	EntityManager eManager;
	//ButtonManager bManager;

	//Game Variables
	Player* player;

	//Notification Channel
	std::string notificationMessage; //Appears on the top of the screen
	float showNotifUntil; //Shows notification until time;

	//Interaction
	bool isInteracting;
	float interactionElapsed; //Total time spent in Interaction instance
	bool canInteractWithSomething;
	int completedInteractionsCount[INTERACTION_COUNT]; //Everytime you finish one interaction of any type, it'll add 1 to here.

		//Queued Message, commands to execute when message is brought up
	std::vector<Interaction*> queuedMessages;
	int currentMessage;

	INTERACTION_TYPE currentInteractionType;
	GEOMETRY_TYPE characterOnUI; //When interacting if there is a person talking to you
	
	Light light[3];

	bool hitboxEnable;
	float fps;

	float toggleTimer = 0;

	void RenderSkybox();
	void RenderUI();
	void initCollidables(Vector3 v3, Vector3 v3R, Vector3 v3S, GEOMETRY_TYPE geoType);
	void SpawnWalls();

	//topdown cam map
	bool camMap;

	bool eHeld = false;

	float CameraBobber = 0;
	double bobTime = 0;

public:
	SceneGarage();
	~SceneGarage();

	//Notifications

	virtual void Init();
	virtual void Update(double dt);
	virtual void InitLights();
	virtual void CollisionHandler(double dt);
	virtual void MissionCompleteListener(double dt);
	virtual void TopDownMapUpdate(double dt);
	virtual void Render();
	virtual void Exit();
};

#endif