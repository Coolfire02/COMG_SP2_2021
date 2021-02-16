#include "Game.h"
SCENES Game::activeScene;

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

void Game::switchScene(static SCENES scene)
{
	activeScene = scene;
}

Scene* Game::getSceneByString(std::string scene)
{
	for (int i = 0; i < SceneList.size(); ++i)
		if (SceneList[i]->getName() == scene)
			return SceneList[i];
}

Scene* Game::getScene()
{
	return SceneList[activeScene];
}
