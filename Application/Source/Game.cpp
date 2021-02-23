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
	/*bManager.setScene(SceneList[activeScene]);
	iManager.initInteractions("TextData//test.txt");

	Button* interactionButton;
	interactionButton = new Button(SceneList[activeScene], "InteractionButton", 64, 36, 64, 36, GEO_QUAD);
	interactionButton->spawnTextObject("", Color(0, 1, 0), CALIBRI, 1.f);
	bManager.addButton(interactionButton);
	bManager.deactivateButton("InteractionButton");

	Button* button;
	button = new Button(SceneList[activeScene], "UIHealth", 40, 5, 40, 5, UI_BLUE);
	button->spawnTextObject("Text", Color(0, 1, 0), CALIBRI, 1);
	button->getTextObject()->setTextString("Test");
	button->getTextObject()->setTextOffsetFromTopLeft(1, 1);
	bManager.addButton(button);*/

}

void Game::Update(double dt)
{
	uiManager.Update(SceneList[activeScene], dt);
	if (uiManager.getCurrentMenu() != UI_MAIN_MENU)
	{
		SceneList[activeScene]->elapser(dt);
		SceneList[activeScene]->Update(dt);
	}
}

void Game::InteractionUpdate(double dt)
{
	if (Game::iManager.getQueue().size() != 0) {
		uiManager.setCurrentUI(UI_INTERACTION);

		uiManager.getByTypeBM(UI_INTERACTION)->activateButton("InteractionButton");
		uiManager.getByTypeBM(UI_INTERACTION)->getButtonByName("InteractionButton")->setText(Game::iManager.getQueue().Top()->interactionText);
	}
	else {
		uiManager.getByTypeBM(UI_INTERACTION)->deactivateButton("InteractionButton");
		Application::setCursorEnabled(false);
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