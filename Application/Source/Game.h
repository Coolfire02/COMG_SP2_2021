#pragma once
#include "Scene.h"
#include <iostream>
#include <vector>

enum SCENES
{
	S_2051 = 0,
	S_MAINWORLD,
	S_COUNT
};

class Game
{
public:
	Game();
	~Game();

	static SCENES activeScene;
	std::vector<Scene*> SceneList;

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	void addScene(Scene* scene);
	void switchScene(static SCENES);
	Scene* getSceneByString(std::string);
	Scene* getScene();
};

