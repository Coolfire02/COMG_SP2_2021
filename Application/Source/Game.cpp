#include "Game.h"
#include "Debug.h"
#include "Application.h"
#include "LoadTGA.h"

// Initialisation of static variables.

bool Game::settings[SETTINGS_COUNT];
float Game::FPS = 60.f;

SCENES Game::activeScene;
SCENES Game::prevScene = S_HOUSEFIRE;
std::vector<Scene*> Game::SceneList;
MissionManager Game::mManager;
InteractionManager Game::iManager;
double Game::gElapsedTime = 0.0;
double Game::sceneCooldown = 0.0;
int Game::ammo = 0;
int Game::cash = 0;

int Game::BimsterSavePoints = 0;
bool Game::killedBimster = false;
bool Game::switchingScene = false;
SCENES Game::toSwitchScene = S_COUNT;
double Game::timeToSwitch = 0.0;
double Game::startSwitchTime = 0.0;

Inventory Game::inv;
UIManager Game::uiManager;
bool Game::gameExit = false;


Game::Game()
{
	ammo = 0;
	cash = 0;
}

Game::~Game()
{
}

/******************************************************************************/
/*!
\brief
Initialises the UI and Interactions here.
*/
/******************************************************************************/
void Game::Init()
{
	iManager.initInteractions("config//Interactions//Interactions.txt");
	uiManager.Init();
}
// tickers for the fire gif.
int frameTicker;
int fireFrame;


/******************************************************************************/
/*!
\brief
Updates all of the game stuff here,
e.g. current Scene, UI, Interactions, Inventory
*/
/******************************************************************************/
void Game::Update(double dt)
{

	sceneCooldown += dt;
	gElapsedTime += dt;
	FPS = 1 / dt;

	if (switchingScene) {
		if (Game::uiManager.getCurrentMenu() != UI_SCENE_TRANSITION) //Fix if anything tries overriding UI_SCENE_TRANSITION process midway through, there is still the prevUIMenu that will save it and its used for revertion later on anyways.
			Game::uiManager.setCurrentUI(UI_SCENE_TRANSITION);
		Button* button = Game::uiManager.getCurrentBM()->getButtonByName("TransitionBackground");
		Button* txt = Game::uiManager.getCurrentBM()->getButtonByName("TransitionText");
		if (timeToSwitch < Game::gElapsedTime) {
			switchingScene = false;
			toSwitchScene = S_COUNT;
			Game::uiManager.setCurrentUI(Game::uiManager.getPrevMenu());
			button->setOrigin(-64, 36);
			txt->setOrigin(20, 32);
			Game::uiManager.getCurrentBM()->deactivateButton("TransitionBackground");
			Game::uiManager.getCurrentBM()->deactivateButton("TransitionText");
		}
		else {
			float totalAniTime = timeToSwitch - startSwitchTime;
			float timeTillEnd = timeToSwitch - Game::gElapsedTime;
			float quaterOfTotalTime = totalAniTime / 4.0;
			if (timeTillEnd > 3 * quaterOfTotalTime) {
				button->setOrigin(button->getUIInfo().originX + 84 * dt * quaterOfTotalTime, button->getUIInfo().originY);
			}
			else if (timeTillEnd < quaterOfTotalTime) {
				button->setOrigin(button->getUIInfo().originX - 84 * dt * quaterOfTotalTime, button->getUIInfo().originY);
				txt->disable();

			}
			else {
				if (!txt->isEnabled()) {
					switchScene(toSwitchScene);
					txt->enable();
				}
			}
		}
	}

	if (GetAsyncKeyState(VK_ESCAPE) & 0x0001)
	{
		if (Game::uiManager.getCurrentMenu() == UI_PAUSE_MENU)
			Game::uiManager.setCurrentUI(UI_GENERAL);
		else if (Game::uiManager.getCurrentMenu() == UI_GENERAL)
			Game::uiManager.setCurrentUI(UI_PAUSE_MENU);
		else if (Game::uiManager.getCurrentMenu() == UI_CREDITS)
			Game::uiManager.setCurrentUI(UI_MAIN_MENU);
		else if (Game::uiManager.getCurrentMenu() == UI_SETTINGS)
			Game::uiManager.setCurrentUI(Game::uiManager.getPrevMenu());
		else if (Game::uiManager.getCurrentMenu() == UI_MAIN_MENU)
			Game::gameExit = true;
	}
	if (Game::settings[SETTINGS::SETTING_SAND_BOX_MODE]) {
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
	}
	if (Game::cash >= 9999999)
		Game::cash = 9999999;

	inv.Update(dt);
	InteractionUpdate(dt);
	mManager.Update(dt);
	uiManager.Update(SceneList[activeScene], dt);
	if (uiManager.getCurrentMenu() != UI_PAUSE_MENU)
	{
		SceneList[activeScene]->elapser(dt);
		SceneList[activeScene]->Update(dt);
	}

	if (frameTicker % 2 == 0) {
		MeshHandler::getMesh(GEO_FIRE_GIF)->textureID = MeshHandler::fireTGAs[fireFrame % 10];
		++fireFrame;
	}
	++frameTicker;
}

/******************************************************************************/
/*!
\brief
Updates the Interaction UI here.
*/
/******************************************************************************/
void Game::InteractionUpdate(double dt)
{

	if (iManager.isInteracting()) {
		if (uiManager.getCurrentMenu() != UI_INTERACTION)
			uiManager.setCurrentUI(UI_INTERACTION);

		// Set all 4 choice buttons to deactivated by default. Only activate if there are choices available.
		uiManager.getCurrentBM()->deactivateButton("Choice1");
		uiManager.getCurrentBM()->deactivateButton("Choice2");
		uiManager.getCurrentBM()->deactivateButton("Choice3");
		uiManager.getCurrentBM()->deactivateButton("Choice4");
		if (iManager.getQueue().Top()->interactionChoices.size() != 0) {
			for (int i = 1; i < iManager.getQueue().Top()->interactionChoices.size() + 1; ++i) {
				std::stringstream ss;
				ss << "Choice" << i;
				// if the length of the string is greater than 2 lines, decrease font size and move the y offset up.
				std::size_t pos = Game::iManager.getQueue().Top()->interactionChoices[i - 1]->interactionText.find("\n");
				if (Game::iManager.getQueue().Top()->interactionChoices[i - 1]->interactionText.find("\n") != std::string::npos && pos != Game::iManager.getQueue().Top()->interactionChoices[i - 1]->interactionText.size() - 1) {
					uiManager.getCurrentBM()->getButtonByName(ss.str())->getTextObject()->setSize(2.5f);
					uiManager.getCurrentBM()->getButtonByName(ss.str())->getTextObject()->setTextOffsetFromTopLeft(9, 3.5);
				} // else render as normal.
				else {
					uiManager.getCurrentBM()->getButtonByName(ss.str())->getTextObject()->setSize(3.5f);
					uiManager.getCurrentBM()->getButtonByName(ss.str())->getTextObject()->setTextOffsetFromTopLeft(9, 5.5);
				}
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

/******************************************************************************/
/*!
\brief
Renders the UI according to the active scene.
*/
/******************************************************************************/
void Game::RenderUI()
{
	uiManager.Render(SceneList[activeScene]);
}

/******************************************************************************/
/*!
\brief
Renders the active scene to the GLFW Window.
*/
/******************************************************************************/
void Game::Render()
{
	SceneList[activeScene]->Render();
}

/******************************************************************************/
/*!
\brief
Cleans up the scenes here.
*/
/******************************************************************************/
void Game::Exit()
{
	for (int i = 0; i < SceneList.size(); i++)
	{
		SceneList[i]->Exit();
		delete SceneList[i];
	}
}

/******************************************************************************/
/*!
\brief
Adds a scene to the SceneList vector.
*/
/******************************************************************************/
void Game::addScene(Scene* scene)
{
	SceneList.push_back(scene); //push back scene into SceneList vector
	scene->Init();
}

/******************************************************************************/
/*!
\brief
Switches the scene using the activeScene enum and intialises light parameters.
*/
/******************************************************************************/
void Game::switchScene(static SCENES scene)
{
	activeScene = scene; //set scene argument to activeScene
	SceneList[scene]->InitLights();
	Game::sceneCooldown = 0;
}

/******************************************************************************/
/*!
\brief
Overloaded scene switching function for scene transitions.
*/
/******************************************************************************/
void Game::switchScene(static SCENES scene, float transitionTime, std::string text)
{
	if (switchingScene != true) {
		switchingScene = true;
		startSwitchTime = Game::gElapsedTime;
		timeToSwitch = Game::gElapsedTime + transitionTime;
		toSwitchScene = scene;
		Game::uiManager.setCurrentUI(UI_SCENE_TRANSITION);
		Game::uiManager.getCurrentBM()->activateButton("TransitionBackground");
		Game::uiManager.getCurrentBM()->getButtonByName("TransitionBackground")->setOrigin(-64, 36);
		Game::uiManager.getCurrentBM()->getButtonByName("TransitionText")->setText(text);
	}
}


/******************************************************************************/
/*!
\brief
returns the active scene.
*/
/******************************************************************************/
Scene* Game::getActiveScene() {
	return SceneList[activeScene];
}

/******************************************************************************/
/*!
\brief
Returns the scene given the string name.
*/
/******************************************************************************/
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

/******************************************************************************/
/*!
\brief
Returns the previous scene's enum type.
*/
/******************************************************************************/
SCENES Game::getPrevSceneENUM()
{
	return prevScene;
}

/******************************************************************************/
/*!
\brief
Sets the previous scene enum.
*/
/******************************************************************************/
void Game::setPrevSceneENUM(SCENES p)
{
	prevScene = p;
}