#ifndef SCENE_2021_H
#define SCENE_2021_H

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
#include "UIManager.h"
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

class Scene2021 : public Scene
{
	enum INTERACTION_TYPE {
		TEST,
		INTERACTION_COUNT,
	};

private:

	Camera camera;
	Camera camera2;

	EntityManager eManager;
	ButtonManager bManager;
	UIManager uiManager;

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
	float BoostMeterGauge = 0;

	void RenderSkybox();
	void RenderRoads();
	void RenderUI();
	void initBuildings(Vector3 v3, Vector3 v3R, Vector3 v3S, GEOMETRY_TYPE geoType);
	void initStreetLamps(Vector3 v3T, Vector3 v3R, Vector3 v3S, GEOMETRY_TYPE geoType);
	void SpawnBuildings();
	void SpawnStreetLamps();
	void SpawnNPCs(Vector3 v3Tmin, Vector3 v3Tmax, NPCTYPE geoType);
	void RenderTexts();
	//topdown cam map
	bool camMap;

	bool eHeld = false;

	float CameraBobber = 0;
	double bobTime = 0;

	double interactionTimer = 0;

public:
	Scene2021();
	~Scene2021();

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