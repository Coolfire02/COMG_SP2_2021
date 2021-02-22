#include "Game.h"
SCENES Game::activeScene;
std::vector<Scene*> Game::SceneList;

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init()
{
	addScene(new SceneAssignment2);
	addScene(new Scene2021);
	addScene(new SceneGunShop);
	addScene(new SceneGarage);
}

void Game::Update(double dt)
{
	SceneList[activeScene]->elapser(dt);
	SceneList[activeScene]->Update(dt);
}

void Game::Render()
{
	SceneList[activeScene]->Render();
}

void Game::Exit()
{
	for (int i = 0; i < SceneList.size(); i++)
	{
		SceneList[i]->Exit();
		delete SceneList[i];
	}
}

void Game::addScene(Scene* scene)
{
	SceneList.push_back(scene); //push back scene into SceneList vector
	scene->Init();
}

void Game::switchScene(static SCENES scene)
{
	activeScene = scene; //set scene argument to activeScene
}

Scene* Game::getSceneByName(std::string scene)
{
	for (int i = 0; i < SceneList.size(); ++i) //find the scene through name
		if (SceneList[i]->getName() == scene) //check if same name as argument
			return SceneList[i]; //return scene
}

Scene* Game::getScene()
{
	return SceneList[activeScene]; //return ActiveScene
}