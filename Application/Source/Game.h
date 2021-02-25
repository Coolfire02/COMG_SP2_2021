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
	S_2051 = 0,
	S_2021,
	S_GUNSHOP,
	S_GARAGE,
	S_GUARD,
	S_HOUSEFIRE,
	S_COUNT
};

//Interface

class Game
{
public:
	Game();
	~Game();
	
	static SCENES activeScene;
	static std::vector<Scene*> SceneList;
	static int ammo;
	static double gElapsedTime;

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
	static Scene* getActiveScene();
	static Scene* getSceneByName(std::string);
	static Scene* getScene();
};
