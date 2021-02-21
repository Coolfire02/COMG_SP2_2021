#pragma once
#include "Scene.h"
#include <iostream>
#include <vector>
#include "Scene.h"
#include "Weapon.h"

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

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	void addScene(Scene* scene);
	void switchScene(static SCENES);
	Scene* getSceneByName(std::string);
	Scene* getScene();
};
