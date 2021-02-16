#pragma once
#include "Source/Scene.h"
#include <iostream>
#include <vector>

enum SCENES
{
	S_2051 = 0,
	S_MAINWORLD,
	S_COUNT
};

class Game : public Scene
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
	Scene* switchScene(static SCENES);
	Scene* getSceneByString(std::string);
	Scene* getScene();
};

