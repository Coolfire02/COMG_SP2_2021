#pragma once
#include "Scene.h"
#include <iostream>
#include <vector>
#include "Scene.h"
#include "Weapon.h"
#include "MissionManager.h"
#include "InteractionManager.h"

class InteractionManager;

enum SCENES
{
	S_2051 = 0,
	S_2021,
	S_GUNSHOP,
	S_GARAGE,
	S_COUNT
};

class Game
{
public:
	Game();
	~Game();
	
	static SCENES activeScene;
	static std::vector<Scene*> SceneList;

	static MissionManager mManager;
	
	static void Init();
	static void Update(double dt);
	static void Render();
	static void Exit();

	static void addScene(Scene* scene);
	static void switchScene(static SCENES);
	static Scene* getSceneByName(std::string);
	static Scene* getScene();
};
