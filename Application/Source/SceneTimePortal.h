#ifndef SCENE_TIMEPORTAL_H
#define SCENE_TIMEPORTAL_H

#include <map>

#include "Scene.h"
#include "Camera.h"
#include "Game.h"
#include "Inventory.h"
#include "MeshBuilder.h"
#include "MatrixStack.h"
#include "Light.h"

#include "EntityManager.h"
#include "MeshHandler.h"
#include "ButtonManager.h"
#include "AudioHandler.h"
#include "InteractionManager.h"

//Entities
#include "NPC.h"
#include "CustomEntity.h"
#include "WorldObject.h"

/******************************************************************************/
/*!
\file	SceneTimePortal.h
\author Joash Foo
\brief
Time Portal Scene to enter and come back from the Future.
*/
/******************************************************************************/

/*
* Scene Setup
* In Init,
Change Scene Name Accordingly
Init the Player Entity

TODOs:
Migrate Most Interaction Handling to Interaction Manager
*/

/******************************************************************************/
/*!
		Class SceneTimePortal:
\brief Time Portal Scene to enter and come back from the Future.
*/
/******************************************************************************/
class SceneTimePortal : public Scene
{
	enum INTERACTION_TYPE {
		TEST,
		INTERACTION_COUNT,
	};

private:
	//Notification Channel
	//std::string notificationMessage; //Appears on the top of the screen
	//float showNotifUntil; //Shows notification until time;

	////Interaction
	//bool isInteracting;
	//float interactionElapsed; //Total time spent in Interaction instance
	//bool canInteractWithSomething;
	//int completedInteractionsCount[INTERACTION_COUNT]; //Everytime you finish one interaction of any type, it'll add 1 to here.

	//	//Queued Message, commands to execute when message is brought up
	//std::vector<Interaction*> queuedMessages;
	//int currentMessage;

	//INTERACTION_TYPE currentInteractionType;
	//GEOMETRY_TYPE characterOnUI; //When interacting if there is a person talking to you

	//double latestInteractionSwitch; //Use counter to only allow interaction switching every 0.5s
	//bool passedInteractCooldown(); //Checks if cooldown is reached;
	//void nextInteraction(); //Handles the next interaction (May end interaction if there is no more to go through0
	void RenderUI(); //Handles the next interaction (May end interaction if there is no more to go through0
	void SpawnNPCs(Vector3 v3Tmin, Vector3 v3Tmax, NPCTYPE geoType);

	Light light[3];
	ButtonManager bManager;

	bool hitboxEnable;
	float fps;
	double endTimer;
	float toggleTimer = 0; //Used for toggling between items

	void RenderSkybox();
	// void split(std::string txt, char delim, std::vector<std::string>& out);

	//topdown cam map
	bool camMap;

	float CameraBobber = 0;
	double bobTime = 0;

	bool canEnd = false;
public:
	SceneTimePortal();
	~SceneTimePortal();

	ISound* fireSound;
	ISound* portalSound;
	bool blackScreen = false;

	bool eHeld = false;
	Camera camera;
	Camera camera2;

	EntityManager eManager;

	//Game Variables
	Player* player;

	//Notifications
	//void sendNotification(std::string msg, double duration);

	//bool runCommand(std::string cmd);
	//bool loadInteractions(INTERACTION_TYPE type);
	//void EndInteraction();

	virtual void Init();
	virtual void Update(double dt);
	virtual void InitLights();
	virtual void CollisionHandler(double dt);
	virtual void MissionCompleteListener(double dt);
	virtual void Render();
	virtual void Exit();
};

#endif
