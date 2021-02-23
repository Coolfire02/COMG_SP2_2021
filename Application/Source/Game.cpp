#include "Game.h"
#include "Debug.h"
#include "Application.h"

SCENES Game::activeScene;
std::vector<Scene*> Game::SceneList;
MissionManager Game::mManager;
InteractionManager Game::iManager;
Inventory Game::inv;
ButtonManager Game::bManager;
UIManager Game::uiManager;
float Game::toggleTimer = 0;

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init()
{
	bManager.setScene(SceneList[activeScene]);
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
	bManager.addButton(button);

	Button* inventoryBackground;
	inventoryBackground = new Button(SceneList[activeScene], "UIInventoryBackground", 64, 36, 100, 48, UI_WINDOW);
	bManager.addButton(inventoryBackground);
	bManager.deactivateButton("UIInventoryBackground");

	Button* itemsButton;
	itemsButton = new Button(SceneList[activeScene], "UIItemsInventory", 21.5, 63, 15, 5, UI_WINDOW);
	itemsButton->spawnTextObject("Text", Color(0, 0, 0), CALIBRI, 1);
	itemsButton->getTextObject()->setTextString("Item");
	itemsButton->getTextObject()->setTextOffsetFromTopLeft(2, 5);
	bManager.addButton(itemsButton);
	bManager.deactivateButton("UIItemsInventory");

	Button* itemsBlankButton;
	itemsBlankButton = new Button(SceneList[activeScene], "UIItemsInventoryBlank", 21.5, 63, 15, 5, UI_WINDOW);
	itemsBlankButton->spawnTextObject("Text", Color(1, 0.3, 0.3), CALIBRI, 1);
	itemsBlankButton->getTextObject()->setTextString("Item");
	itemsBlankButton->getTextObject()->setTextOffsetFromTopLeft(2, 5);
	bManager.addButton(itemsBlankButton);
	bManager.deactivateButton("UIItemsInventoryBlank");

	Button* weaponsButton;
	weaponsButton = new Button(SceneList[activeScene], "UIWeaponsInventory", 36.5, 63, 15, 5, UI_WINDOW);
	weaponsButton->spawnTextObject("Text", Color(0, 0, 0), CALIBRI, 1);
	weaponsButton->getTextObject()->setTextString("Guns");
	weaponsButton->getTextObject()->setTextOffsetFromTopLeft(2, 5);
	bManager.addButton(weaponsButton);
	bManager.deactivateButton("UIWeaponsInventory");

	Button* weaponsBlankButton;
	weaponsBlankButton = new Button(SceneList[activeScene], "UIWeaponsInventoryBlank", 36.5, 63, 15, 5, UI_WINDOW);
	weaponsBlankButton->spawnTextObject("Text", Color(1, 0.3, 0.3), CALIBRI, 1);
	weaponsBlankButton->getTextObject()->setTextString("Guns");
	weaponsBlankButton->getTextObject()->setTextOffsetFromTopLeft(2, 5);
	bManager.addButton(weaponsBlankButton);
	bManager.deactivateButton("UIWeaponsInventoryBlank");

	Button* garageButton;
	garageButton = new Button(SceneList[activeScene], "UIGarageInventory", 51.5, 63, 15, 5, UI_WINDOW);
	garageButton->spawnTextObject("Text", Color(0, 0, 0), CALIBRI, 1);
	garageButton->getTextObject()->setTextString("Cars");
	garageButton->getTextObject()->setTextOffsetFromTopLeft(2, 5);
	bManager.addButton(garageButton);
	bManager.deactivateButton("UIGarageInventory");

	Button* garageBlankButton;
	garageBlankButton = new Button(SceneList[activeScene], "UIGarageInventoryBlank", 51.5, 63, 15, 5, UI_WINDOW);
	garageBlankButton->spawnTextObject("Text", Color(1, 0.3, 0.3), CALIBRI, 1);
	garageBlankButton->getTextObject()->setTextString("Cars");
	garageBlankButton->getTextObject()->setTextOffsetFromTopLeft(2, 5);
	bManager.addButton(garageBlankButton);
	bManager.deactivateButton("UIGarageInventoryBlank");

	Button* titleBackground;
	titleBackground = new Button(SceneList[activeScene], "TitleBackground", 64, 36, 128, 72, TITLE_BG);
	bManager.addButton(titleBackground);
	bManager.deactivateButton("TitleBackground");

	Button* playButton;
	playButton = new Button(SceneList[activeScene], "MainMenuPlayButton", 64, 36, 16, 12, PLAY_BUTTON);
	bManager.addButton(playButton);
	bManager.deactivateButton("MainMenuPlayButton");
}

void Game::Update(double dt)
{
	bManager.setScene(SceneList[activeScene]);
	iManager.Update(dt);
	mManager.Update(dt);
	bManager.Update(dt);

	if (Application::IsKeyPressed('E')) //pick up weapon
		//inv.addWeap(PISTOL);
	if (Application::IsKeyPressed('F')) //pick up weapon
		inv.addWeap(SILENCER);
	if (GetAsyncKeyState('1') & 0x0001) //weapon slot 1
		inv.switchWeapon(0);
	if (GetAsyncKeyState('2') & 0x0001) //weapon slot 2
		inv.switchWeapon(1);
	if (GetAsyncKeyState('3') & 0x0001) //weapon slot 3
		inv.switchWeapon(2);
	if (GetAsyncKeyState('4') & 0x0001) //weapon slot 4
		inv.switchWeapon(3);
	if (toggleTimer > 1 && Application::IsKeyPressed('O')) //delete equipped weapon
	{
		toggleTimer = 0;
		inv.deleteWeapon(Game::inv.getActiveWeapon()->getWeaponType());
	}

	if (Application::IsKeyPressed('F'))
	{
		Game::inv.addItem(BURGER, 1);
		Game::inv.addItem(EGGPLANT, 2);

		Game::inv.addCar(SUV);
	}
	if (toggleTimer > 1 && Application::IsKeyPressed('L'))
	{
		toggleTimer = 0;
		if (uiManager.getCurrentMenu() == GENERAL_UI)
		{
			uiManager.setCurrentMenu(ITEM_INVENTORY);
		}
		else
		{
			uiManager.setCurrentMenu(GENERAL_UI);
			bManager.deactivateButton("UIInventoryBackground");
			bManager.deactivateButton("UIItemsInventoryBlank");
			bManager.deactivateButton("UIWeaponsInventory");
			bManager.deactivateButton("UIGarageInventory");
		}

		/*inv.toggleItem();
		if (inv.getCurrentCarType() == SEDAN)
			inv.switchCar(SUV);
		else
			inv.switchCar(SEDAN);*/
	}

	InteractionUpdate(dt);
	ButtonUpdate(dt);
	SceneList[activeScene]->elapser(dt);
	SceneList[activeScene]->Update(dt);
}

void Game::ButtonUpdate(double dt) {
	bool ePressed = Application::IsKeyPressed('E');
	bool pPressed = Application::IsKeyPressed('P');
	bool tPressed = Application::IsKeyPressed('T');

	//Button Interaction Handling
	// bManager.Update(dt);

	for (auto& buttonCollide : bManager.getButtonsInteracted()) {
		if (buttonCollide->buttonClicked->getName() == "UIHealth" && buttonCollide->justClicked) {
			DEBUG_MSG("Clicked");
		}
		if (buttonCollide->buttonClicked->getName() == "UIHealth" && buttonCollide->isClicking) {
			DEBUG_MSG("Is Clicking");
		}
		if (buttonCollide->buttonClicked->getName() == "UIHealth" && buttonCollide->justHovered) {
			DEBUG_MSG("Hovered");
		}
		if ((buttonCollide->buttonClicked->getName() == "MainMenuPlayButton" && buttonCollide->justClicked) || Application::IsKeyPressed(VK_LEFT)) { //Main Menu play button
			uiManager.setCurrentMenu(GENERAL_UI);
			bManager.deactivateButton("TitleBackground");
			bManager.deactivateButton("MainMenuPlayButton");
		}
		if (buttonCollide->buttonClicked->getName() == "UIItemsInventory" && buttonCollide->justClicked) { //Click item inventory
			if (uiManager.getCurrentMenu() == WEAPON_INVENTORY)
			{
				uiManager.setCurrentMenu(ITEM_INVENTORY);
				bManager.deactivateButton("UIInventoryBackground");
				bManager.deactivateButton("UIItemsInventory");
				bManager.deactivateButton("UIWeaponsInventoryBlank");
				bManager.deactivateButton("UIGarageInventory");
			}
			else
			{
				uiManager.setCurrentMenu(ITEM_INVENTORY);
				bManager.deactivateButton("UIInventoryBackground");
				bManager.deactivateButton("UIItemsInventory");
				bManager.deactivateButton("UIWeaponsInventory");
				bManager.deactivateButton("UIGarageInventoryBlank");
			}
		}
		if (buttonCollide->buttonClicked->getName() == "UIWeaponsInventory" && buttonCollide->justClicked) { //Click weapon inventory
			if (uiManager.getCurrentMenu() == ITEM_INVENTORY)
			{
				uiManager.setCurrentMenu(WEAPON_INVENTORY);
				bManager.deactivateButton("UIInventoryBackground");
				bManager.deactivateButton("UIItemsInventoryBlank");
				bManager.deactivateButton("UIWeaponsInventory");
				bManager.deactivateButton("UIGarageInventory");
			}
			else
			{
				uiManager.setCurrentMenu(WEAPON_INVENTORY);
				bManager.deactivateButton("UIInventoryBackground");
				bManager.deactivateButton("UIItemsInventory");
				bManager.deactivateButton("UIWeaponsInventory");
				bManager.deactivateButton("UIGarageInventoryBlank");
			}
		}
		if (buttonCollide->buttonClicked->getName() == "UIGarageInventory" && buttonCollide->justClicked) { //Click weapon inventory
			if (uiManager.getCurrentMenu() == ITEM_INVENTORY)
			{
				uiManager.setCurrentMenu(GARAGE_INVENTORY);
				bManager.deactivateButton("UIInventoryBackground");
				bManager.deactivateButton("UIItemsInventoryBlank");
				bManager.deactivateButton("UIWeaponsInventory");
				bManager.deactivateButton("UIGarageInventory");
			}
			else
			{
				uiManager.setCurrentMenu(GARAGE_INVENTORY);
				bManager.deactivateButton("UIInventoryBackground");
				bManager.deactivateButton("UIItemsInventory");
				bManager.deactivateButton("UIWeaponsInventoryBlank");
				bManager.deactivateButton("UIGarageInventory");
			}
		}
		if (buttonCollide->buttonClicked->getName() == "InteractionButton" && buttonCollide->justClicked) {
			Game::iManager.EndInteraction();
			if (Game::iManager.getQueue().size() != 0)
				Game::iManager.nextInteraction();
			DEBUG_MSG("next Interaction");
		}
	}
	if (pPressed) Application::setCursorEnabled(true);
}

void Game::InteractionUpdate(double dt)
{
	if (Game::iManager.getQueue().size() != 0) {
		bManager.activateButton("InteractionButton");
		bManager.getButtonByName("InteractionButton")->setText(Game::iManager.getQueue().Top()->interactionText);
	}
	else {
		bManager.deactivateButton("InteractionButton");
		Application::setCursorEnabled(false);
	}
}

void Game::Render()
{
	SceneList[activeScene]->Render();
	RenderUI();
	for (auto& button : bManager.getButtons()) {
		button->Render();
	}

}

void Game::RenderUI()
{
	std::ostringstream ss;
	switch (uiManager.getCurrentMenu())
	{
		//if (i >= (Game::inv.getWeaponVector().size())) //if more than 4 weapons owned, return (don't show weapon in UI)
			//return;

	case GENERAL_UI:
		//GUI
		//Ammo
		ss.str("");
		ss.clear();
		ss << "6/30";
		SceneList[activeScene]->RenderTextOnScreen(MeshHandler::getMesh(GEO_TEXT), ss.str(), Color(1, 1, 1), 4, 94, 20);

		//Current Item Amount
		if (Game::inv.getItemInventory() != nullptr)
		{
			ss.str("");
			ss.clear();
			ss << Game::inv.getCurrentItemAmt();
			SceneList[activeScene]->RenderTextOnScreen(MeshHandler::getMesh(GEO_TEXT), ss.str(), Color(1, 1, 1), 4, 115, 25);
		}

		//Item UI
		switch (Game::inv.getCurrentItemType())
		{
		case BURGER:
			SceneList[activeScene]->RenderMeshOnScreen(MeshHandler::getMesh(UI_BURGER), 120, 20, 10, 10);
			break;
		case CORN:
			SceneList[activeScene]->RenderMeshOnScreen(MeshHandler::getMesh(UI_CORN), 120, 20, 10, 10);
			break;
		case EGGPLANT:
			SceneList[activeScene]->RenderMeshOnScreen(MeshHandler::getMesh(UI_EGGPLANT), 120, 20, 10, 10);
			break;
		default:
			SceneList[activeScene]->RenderMeshOnScreen(MeshHandler::getMesh(UI_EMPTY), 120, 20, 10, 10);
			break;
		}
		SceneList[activeScene]->RenderMeshOnScreen(MeshHandler::getMesh(UI_BLUE), 120, 20, 11, 11);

		//Weapons UI
		for (int i = 0; i < 4; i++) //limit to displaying 4
		{
			if (i >= (Game::inv.getWeaponVector().size())) //if more than 4 weapons owned, return (don't show weapon in UI)
				return;

			switch (Game::inv.getWeaponVector()[i]->getWeaponType())
			{
			case PISTOL:
				SceneList[activeScene]->RenderMeshOnScreen(MeshHandler::getMesh(UI_PISTOL), 90 + (i * 10), 10, 10, 10);
				break;
			case SILENCER:
				SceneList[activeScene]->RenderMeshOnScreen(MeshHandler::getMesh(UI_SILENCER), 90 + (i * 10), 10, 10, 10);
				break;
			default:
				SceneList[activeScene]->RenderMeshOnScreen(MeshHandler::getMesh(UI_EMPTY), 90 + (i * 10), 10, 10, 10);
				break;
			}
			SceneList[activeScene]->RenderMeshOnScreen(MeshHandler::getMesh(UI_BLACK), 90 + (i * 10), 10, 10, 10);
			if (Game::inv.getWeaponVector()[i]->getWeaponType() == Game::inv.getActiveWeapon()->getWeaponType())
			{
				SceneList[activeScene]->RenderMeshOnScreen(MeshHandler::getMesh(UI_BLUE), 90 + (i * 10), 10, 11, 11);
			}
		}
		break;
	case ITEM_INVENTORY:
		bManager.activateButton("UIInventoryBackground");

		bManager.activateButton("UIItemsInventoryBlank");
		bManager.activateButton("UIWeaponsInventory");
		bManager.activateButton("UIGarageInventory");
		break;
	case WEAPON_INVENTORY:
		bManager.activateButton("UIInventoryBackground");

		bManager.activateButton("UIItemsInventory");
		bManager.activateButton("UIWeaponsInventoryBlank");
		bManager.activateButton("UIGarageInventory");
		break;
	case GARAGE_INVENTORY:
		bManager.activateButton("UIInventoryBackground");

		bManager.activateButton("UIItemsInventory");
		bManager.activateButton("UIWeaponsInventory");
		bManager.activateButton("UIGarageInventoryBlank");
		break;
	case MAIN_MENU:
		bManager.activateButton("TitleBackground");
		bManager.activateButton("MainMenuPlayButton");
		break;
	default:
		break;
	}
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