#pragma once
#include "Scene.h"
#include <iostream>
#include <vector>
#include "Weapon.h"
#include "Inventory.h"
#include "MissionManager.h"
#include "UIManager.h"
#include "InteractionManager.h"

/******************************************************************************/
/*!
\file	Game.h
\author Joash Foo
\brief Header file containing the Game class.
*/
/******************************************************************************/

/******************************************************************************/
/*!
\brief
enum to check for active scenes.
*/
/******************************************************************************/
enum SCENES
{
	S_HOUSEFIRE = 0,
	S_GUARD,
	S_TIMEPORTAL,
	S_2021,
	S_GUNSHOP,
	S_GARAGE,
	S_CARSHOP,
	S_OFFICE,
	S_FINALE,
	S_UI,
	S_COUNT
};

/******************************************************************************/
/*!
\brief
enum to check for Settings Interface
*/
/******************************************************************************/
enum SETTINGS {
	SETTING_SAND_BOX_MODE,
	SETTING_FPS,
	SETTINGS_COUNT
};

/******************************************************************************/
/*!
		Class Game:
\brief The Game Class that handles scene management, stores global managers such as Inventories, Interactions, UIs, etc.
*/
/******************************************************************************/
class Game
{

private:
	static bool switchingScene; // boolean to check if the scene is currently being switched.
	static SCENES toSwitchScene; // Scene to be switched to.
	static double timeToSwitch; // time taken to switch.
	static double startSwitchTime; // start of the elapsed switch time.
	static SCENES prevScene; // prev scene stored when going back to the main menu to deter loss of progress.

public:
	Game();
	~Game();

	static bool killedBimster;
	static int BimsterSavePoints; // Points used to calculate whether the last boss should be killed or spared.
	static bool settings[SETTINGS_COUNT];
	static float FPS; // FPS

	static double sceneCooldown; // cooldown so players cant keep switching scenes
	static SCENES activeScene; // current scene
	static std::vector<Scene*> SceneList; // list of scenes
	static int ammo; // total ammo of the player
	static int cash; // money
	static double gElapsedTime;
	static bool gameExit;

	static MissionManager mManager; // Mission Manager
	static InteractionManager iManager; // Interaction Manager
	static UIManager uiManager; // UI Manager
	static Inventory inv; // Inventory

	static void Init();
	static void Update(double dt);
	static void InteractionUpdate(double dt);
	static void RenderUI();
	static void Render();
	static void Exit();

	static void setAmmo(int);
	static int getAmmo();

	static void addScene(Scene* scene);
	static void switchScene(static SCENES);
	static void switchScene(SCENES, float transition, std::string titleText);
	static Scene* getActiveScene();
	static Scene* getSceneByName(std::string);
	static Scene* getScene();

	static SCENES getPrevSceneENUM();
	static void setPrevSceneENUM(SCENES);
};
