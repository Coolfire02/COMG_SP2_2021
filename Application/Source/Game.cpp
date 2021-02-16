#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init()
{
}

void Game::Update(double dt)
{
}

void Game::Render()
{
}

void Game::Exit()
{
}

void Game::addScene(Scene* scene)
{
	SceneList.push_back(scene);
	scene->Init();
}

Scene* Game::switchScene(static SCENES scene)
{
	switch (scene)
	{
	case 0:
		return SceneList[0];
		break;

	}
}

Scene* Game::getSceneByString(std::string scene)
{
	for (int i = 0; i < SceneList.size(); ++i)
		if (sceneName == scene)
			return SceneList[i];
}

Scene* Game::getScene()
{
	return SceneList[activeScene];
}
