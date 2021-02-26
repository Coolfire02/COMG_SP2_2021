#include "Game.h"
#include "Debug.h"
#include "Application.h"
#include "LoadTGA.h"

SCENES Game::activeScene;
std::vector<Scene*> Game::SceneList;
MissionManager Game::mManager;
InteractionManager Game::iManager;
double Game::gElapsedTime = 0.0;
int Game::ammo = 0;
int Game::cash = 0;
Inventory Game::inv;
UIManager Game::uiManager;
bool Game::gameExit = false;

Game::Game()
{
	ammo = 20;
	cash = 0;
}

Game::~Game()
{
}

void Game::Init()
{
	iManager.initInteractions("config//Interactions//Interactions.txt");
	uiManager.Init();
}

int frameTicker;
int fireFrame;
void Game::Update(double dt)
{
	if (GetAsyncKeyState(VK_ESCAPE) & 0x0001)
	{
		if (Game::uiManager.getCurrentMenu() == UI_PAUSE_MENU)
			Game::uiManager.setCurrentUI(UI_GENERAL);
		else if (Game::uiManager.getCurrentMenu() == UI_GENERAL)
			Game::uiManager.setCurrentUI(UI_PAUSE_MENU);
		else if (Game::uiManager.getCurrentMenu() == UI_MAIN_MENU)
			Game::gameExit = true;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x0001) {
		if (Game::activeScene < S_COUNT - 1) {
			Game::activeScene = (SCENES)((int)Game::activeScene + 1);
			SceneList[activeScene]->InitLights();
		}
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x0001) {
		if (Game::activeScene > 0) {
			Game::activeScene = (SCENES)((int)Game::activeScene - 1);
			SceneList[activeScene]->InitLights();
		}
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	if (Game::cash >= 9999999)
		Game::cash = 9999999;
	//if (GetAsyncKeyState('3') & 0x8001) {
	//	Game::switchScene(S_2051);
	//	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//}
	//else if (GetAsyncKeyState('4') & 0x8001) {
	//	Game::switchScene(S_2021);
	//	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//}
	//else if (GetAsyncKeyState('5') & 0x8001) {
	//	//game.switchScene(S_2021);
	//	Game::switchScene(S_GARAGE);
	//	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//}
	//else if (GetAsyncKeyState('6') & 0x8001) {
	//	Game::switchScene(S_GUNSHOP);
	//}
	//else if (GetAsyncKeyState('7') & 0x8001) {
	//	Game::switchScene(S_GUARD);
	//}
	//else if (GetAsyncKeyState('8') & 0x8001) {
	//	Game::switchScene(S_HOUSEFIRE);
	//}

	gElapsedTime += dt;
	inv.Update(dt);
	InteractionUpdate(dt);		
	mManager.Update(dt);
	uiManager.Update(SceneList[activeScene], dt);
	SceneList[activeScene]->elapser(dt);
	SceneList[activeScene]->Update(dt);


	if (frameTicker % 2 == 0) {
		MeshHandler::getMesh(GEO_FIRE_GIF)->textureID = MeshHandler::fireTGAs[fireFrame % 10];
		++fireFrame;
	}
	++frameTicker;
}

void Game::InteractionUpdate(double dt)
{
	
	if (iManager.isInteracting()) {
		if(uiManager.getCurrentMenu() != UI_INTERACTION)
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
	SceneList[scene]->InitLights();
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