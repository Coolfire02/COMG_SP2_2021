#pragma once
#include "Scene.h"
#include <iostream>
#include <vector>
#include "Weapon.h"
#include "Inventory.h"
#include "MissionManager.h"
#include "UIManager.h"
#include "InteractionManager.h"

enum SCENES
{
	S_HOUSEFIRE = 0,
	S_2051,
	S_TIMEPORTAL,
	S_2021,
	S_GUNSHOP,
	S_GARAGE,
	S_GUARD,
	S_CARSHOP,
	S_UI,
	S_OFFICE,
	S_COUNT
};

//Interface

class Game
{

private:
	static bool switchingScene;
	static SCENES toSwitchScene;
	static double timeToSwitch;
	static double startSwitchTime;
	static SCENES prevScene;

public:
	Game();
	~Game();

	static SCENES activeScene;
	static std::vector<Scene*> SceneList;
	static int ammo;
	static int cash;
	static double gElapsedTime;
	static bool gameExit;

	static MissionManager mManager;
	static InteractionManager iManager;
	static UIManager uiManager;
	static Inventory inv;

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
