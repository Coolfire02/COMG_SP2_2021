#include "Game.h"
#include "Debug.h"
#include "Application.h"

SCENES Game::activeScene;
std::vector<Scene*> Game::SceneList;
MissionManager Game::mManager;
InteractionManager Game::iManager;
float Game::toggleTimer = 0;
Inventory Game::inv;
UIManager Game::uiManager;

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init()
{
	iManager.initInteractions("TextData//test.txt");
}

void Game::Update(double dt)
{

	if (Application::IsKeyPressed('E')) //pick up weapon
		//inv.addWeap(PISTOL);
	if (Application::IsKeyPressed('F')) //pick up weapon
		inv.addWeap(SILENCER);
	if (GetAsyncKeyState('1') & 0x0001) //weapon slot 1
		Game::inv.switchWeapon(0);
	if (GetAsyncKeyState('2') & 0x0001) //weapon slot 2
		Game::inv.switchWeapon(1);
	if (GetAsyncKeyState('3') & 0x0001) //weapon slot 3
		Game::inv.switchWeapon(2);
	if (GetAsyncKeyState('4') & 0x0001) //weapon slot 4
		Game::inv.switchWeapon(3);
	if (toggleTimer > 1 && Application::IsKeyPressed('O')) //delete equipped weapon
	{
		toggleTimer = 0;
		Game::inv.deleteWeapon(Game::inv.getActiveWeapon()->getWeaponType());
	}

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