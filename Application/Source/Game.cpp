#include "Game.h"
#include "Debug.h"
#include "Application.h"

SCENES Game::activeScene;
std::vector<Scene*> Game::SceneList;
MissionManager Game::mManager;
InteractionManager Game::iManager;
double Game::gElapsedTime = 0.0;
int Game::ammo = 0;
Inventory Game::inv;
UIManager Game::uiManager;

Game::Game()
{
	ammo = 100;
}

Game::~Game()
{
}

void Game::Init()
{
	iManager.initInteractions("TextData//test.txt");
	uiManager.Init();
}

void Game::Update(double dt)
{
	gElapsedTime += dt;
	inv.Update(dt);
	InteractionUpdate(dt);		
	mManager.Update(dt);
	uiManager.Update(SceneList[activeScene], dt);
	if (uiManager.getCurrentMenu() != UI_MAIN_MENU)
	{
		SceneList[activeScene]->elapser(dt);
		SceneList[activeScene]->Update(dt);
	}
}

void Game::InteractionUpdate(double dt)
{
	if (iManager.isInteracting()) {
		uiManager.setCurrentUI(UI_INTERACTION);
		uiManager.getCurrentBM()->deactivateButton("Choice1");
		uiManager.getCurrentBM()->deactivateButton("Choice2");
		uiManager.getCurrentBM()->deactivateButton("Choice3");
		uiManager.getCurrentBM()->deactivateButton("Choice4");
		if (iManager.getQueue().Top()->interactionChoices.size() != 0) {
			for (int i = 1; i < iManager.getQueue().Top()->interactionChoices.size() + 1; ++i) {
				std::stringstream ss;
				ss << "Choice" << i;
				uiManager.getCurrentBM()->getButtonByName(ss.str())->setText(Game::iManager.getQueue().Top()->interactionChoices[i - 1]->interactionText);
				uiManager.getCurrentBM()->activateButton(ss.str());
			}
		}
		uiManager.getCurrentBM()->activateButton("InteractionButton");
		uiManager.getCurrentBM()->getButtonByName("InteractionButton")->setText(Game::iManager.getQueue().Top()->interactionText);
	}
	else {
		uiManager.getCurrentBM()->deactivateButton("InteractionButton");
	}
}

void Game::RenderUI()
{
	uiManager.Render(SceneList[activeScene]);
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

Scene* Game::getActiveScene() {
	return nullptr;
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