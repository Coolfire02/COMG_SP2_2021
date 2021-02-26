#include "UIManager.h"
#include "Application.h"
#include <cmath>

int UIManager::digitCount(int num) //returns number of digits in parameter
{
	return int(log10(num) + 1);
}

UIManager::UIManager()
{
}

void UIManager::Init() {
	////bManager = bN;
	currentMenu = UI_MAIN_MENU;
	activeMenus[UI_MISSION] = true; //UI_MISSION Overlay

	uiActive = true;
	currentMenu = UI_MAIN_MENU;
	nextKeyPress = 0;

	for (int i = 0; i < UI_MENU_COUNT; i++)
	{
		bManagers[i] = new ButtonManager();
		int row = 0;
		int column = 0;
		switch (i)
		{
		case UI_GENERAL:
			//Items UI
			//need to create text buttons for amount
			createTextButton(bManagers[i], "UIItemAmount", 120, 25, 1, 1, 0, 0, Color(1, 1, 1), "0", 3.0f);
			createNoTextButton(bManagers[i], "UIItem", 120, 20, 10, 10, UI_EMPTY);
			createNoTextButton(bManagers[i], "UIItemCurrent", 120, 20, 11, 11, UI_BLUE);

			//Weapons UI
			createTextButton(bManagers[i], "AmmoCount", 85.5, 8, 1,1, 0,0, Color(1,1,1), "0/0 Ammo", 5.0f);
			createTextButton(bManagers[i], "TotalAmmoCount", 91, 5, 1,1, 0,0, Color(1,0,1), "0", 3.0f);
			
			createNoTextButton(bManagers[i], "Weapon1", 100, 10, 10, 10, UI_PISTOL);
			createNoTextButton(bManagers[i], "Weapon2", 110, 10, 10, 10, UI_SILENCER);
			for (int j = 0; j < WEAPON_COUNT; j++)
			{
				createNoTextButton(bManagers[i], "UIWeaponBorder" + std::to_string(j + 1), 100 + (j * 10), 10, 10, 10, UI_BLACK);
			}
			for (int j = 0; j < WEAPON_COUNT; j++)
			{
				createNoTextButton(bManagers[i], "UIWeaponCurrent" + std::to_string(j + 1), 100 + (j * 10), 10, 11, 11, UI_BLUE);
			}

			//cash
			createTextButton(bManagers[i], "Cash", 120, 65, 1, 1, 0, 0, Color(1, 1, 1), "$" + std::to_string(Game::cash), 5.0f);
			break;
		case UI_ITEM_INVENTORY:
			createNoTextButton(bManagers[i], "UIInventoryBackground", 64, 36, 100, 48, UI_WINDOW);
			createButton(bManagers[i], "UIItemsInventoryBlank", 21.5, 63, 15, 5, UI_WINDOW, 3, 5, Color(1, 0.3, 0.3), "Item", 5.0f);
			createButton(bManagers[i], "UIWeaponsInventory", 36.5, 63, 15, 5, UI_WINDOW, 3, 5, Color(0, 0, 0), "Guns", 5.0f);
			createButton(bManagers[i], "UIGarageInventory", 51.5, 63, 15, 5, UI_WINDOW, 3, 5, Color(0, 0, 0), "Cars", 5.0f);

			createNoTextButton(bManagers[i], "UIItemsInventoryCurrent", 96.5, 47, 15, 15, UI_BLANK);
			createNoTextButton(bManagers[i], "UIItemsInventoryCurrentBorder", 96.5, 47, 15, 15, UI_BLUE);
			createTextButton(bManagers[i], "UIItemsInventoryName", 86.5, 30, 1, 1, 0, 0, Color(0, 0, 0), " ", 5.0f);

			row = 0;
			column = 0;
			for (int j = 0; j < ITEM_AMOUNT; j++)
			{
				if (j % 5 == 0 && j != 0)
				{
					row += 1;
					column = 0;
				}
				createNoTextButton(bManagers[i], "UIItemInventorySlot" + std::to_string(j + 1), 24 + (column * 12), 52 - (row * 12), 10, 10, UI_BLANK);
				createNoTextButton(bManagers[i], "UIItemInventorySlotCurrent" + std::to_string(j + 1), 24 + (column * 12), 52 - (row * 12), 10, 10, UI_BLUE);
				column += 1;
			}
			break;
		case UI_WEAPON_INVENTORY:
			createNoTextButton(bManagers[i], "UIInventoryBackground", 64, 36, 100, 48, UI_WINDOW);
			createButton(bManagers[i], "UIItemsInventory", 21.5, 63, 15, 5, UI_WINDOW, 3, 5, Color(0, 0, 0), "Item", 5.0f);
			createButton(bManagers[i], "UIWeaponsInventoryBlank", 36.5, 63, 15, 5, UI_WINDOW, 3, 5, Color(1, 0.3, 0.3), "Guns", 5.0f);
			createButton(bManagers[i], "UIGarageInventory", 51.5, 63, 15, 5, UI_WINDOW, 3, 5, Color(0, 0, 0), "Cars", 5.0f);

			createNoTextButton(bManagers[i], "UIWeaponsInventoryCurrent", 96.5, 47, 15, 15, UI_BLANK);
			createNoTextButton(bManagers[i], "UIWeaponsInventoryCurrentBorder", 96.5, 47, 15, 15, UI_BLUE);
			createTextButton(bManagers[i], "UIWeaponsInventoryName", 86.5, 30, 1, 1, 0, 0, Color(0, 0, 0), " ", 5.0f);

			row = 0;
			column = 0;
			for (int j = 0; j < WEAPON_COUNT; j++)
			{
				if (j % 5 == 0 && j != 0)
				{
					row += 1;
					column = 0;
				}
				createNoTextButton(bManagers[i], "UIWeaponInventorySlot" + std::to_string(j + 1), 24 + (column * 12), 52 - (row * 12), 10, 10, UI_BLANK);
				createNoTextButton(bManagers[i], "UIWeaponInventorySlotCurrent" + std::to_string(j + 1), 24 + (column * 12), 52 - (row * 12), 10, 10, UI_BLUE);
				column += 1;
			}
			break;
		case UI_GARAGE_INVENTORY:
			createNoTextButton(bManagers[i], "UIInventoryBackground", 64, 36, 100, 48, UI_WINDOW);
			createButton(bManagers[i], "UIItemsInventory", 21.5, 63, 15, 5, UI_WINDOW, 3, 5, Color(0, 0, 0), "Item", 5.0f);
			createButton(bManagers[i], "UIWeaponsInventory", 36.5, 63, 15, 5, UI_WINDOW, 3, 5, Color(0, 0, 0), "Guns", 5.0f);
			createButton(bManagers[i], "UIGarageInventoryBlank", 51.5, 63, 15, 5, UI_WINDOW, 3, 5, Color(1, 0.3, 0.3), "Cars", 5.0f);

			createNoTextButton(bManagers[i], "UIGarageInventoryCurrent", 96.5, 47, 15, 15, UI_BLANK);
			createNoTextButton(bManagers[i], "UIGarageInventoryCurrentBorder", 96.5, 47, 15, 15, UI_BLUE);
			createTextButton(bManagers[i], "UIGarageInventoryName", 86.5, 30, 1, 1, 0, 0, Color(0, 0, 0), " ", 5.0f);

			row = 0;
			column = 0;
			for (int j = 0; j < CAR_COUNT; j++)
			{
				if (j % 5 == 0 && j != 0)
				{
					row += 1;
					column = 0;
				}
				//Need to have increment so that every 5 slots would push the next to next row
				createNoTextButton(bManagers[i], "UIGarageInventorySlot" + std::to_string(j + 1), 24 + (column * 12), 52 - (row * 12), 10, 10, UI_BLANK);
				createNoTextButton(bManagers[i], "UIGarageInventorySlotCurrent" + std::to_string(j + 1), 24 + (column * 12), 52 - (row * 12), 10, 10, UI_BLUE);
				column += 1;
			}
			break;
		case UI_MAIN_MENU:
			createNoTextButton(bManagers[i], "TitleBackground", 64, 36, 128, 72, TITLE_BG);
			createNoTextButton(bManagers[i], "MainMenuPlayButton", 64, 36, 16, 12, PLAY_BUTTON);
			enableUI();
			break;
		case UI_INTERACTION:
			createButton(bManagers[i], "Choice1", 96, 33.7, 58, 7.4, UI_CHOICE, 9, 5.5, Color(1, 1, 1), "", 3.5f);
			createButton(bManagers[i], "Choice2", 96, 43.8, 58, 7.4, UI_CHOICE, 9, 5.5, Color(1, 1, 1), "", 3.5f);
			createButton(bManagers[i], "Choice3", 96, 53.5, 58, 7.4, UI_CHOICE, 9, 5.5, Color(1, 1, 1), "", 3.5f);
			createButton(bManagers[i], "Choice4", 96, 63.2, 58, 7.4, UI_CHOICE, 9, 5.5, Color(1, 1, 1), "", 3.5f);


			createButton(bManagers[i], "InteractionButton", 64, 13.7, 128, 28, UI_TEXTBOX, 3, 12, Color(1, 1, 1), "", 4.0f);
			createButton(bManagers[i], "UIHealth", 40, 5, 40, 5, UI_BLUE, 1, 1, Color(0, 1, 0), "Test", 1.0f);
			break;
		case UI_MISSION:
			createButton(bManagers[i], "MissionComplete", 78, 60, 72, 18, GEO_MISSION_COMPLETE, 16, 7, Color(0.1f, 0.7f, 0.12f), "Test Mission Complete", 3.0f);
			createButton(bManagers[i], "Task0", 17, 70.5, 34, 3, GEO_MISSION_TASK, 2, 2.5, Color(0.9f, 0.9f, 0.9f), "Task | 0% Done", 2.0f);
			createButton(bManagers[i], "Task1", 17, 67.5, 34, 3, GEO_MISSION_TASK, 2, 2.5, Color(0.9f, 0.9f, 0.9f), "Task | 0% Done", 2.0f);
			createButton(bManagers[i], "Task2", 17, 64.5, 34, 3, GEO_MISSION_TASK, 2, 2.5, Color(0.9f, 0.9f, 0.9f), "Task | 0% Done", 2.0f);
			createButton(bManagers[i], "Task3", 17, 61.5, 34, 3, GEO_MISSION_TASK, 2, 2.5, Color(0.9f, 0.9f, 0.9f), "Task | 0% Done", 2.0f);
			createButton(bManagers[i], "Task4", 17, 58.5, 34, 3, GEO_MISSION_TASK, 2, 2.5, Color(0.9f, 0.9f, 0.9f), "Task | 0% Done", 2.0f);
			
			bManagers[i]->deactivateButton("MissionComplete");
			bManagers[i]->deactivateButton("Task0");
			bManagers[i]->deactivateButton("Task1");
			bManagers[i]->deactivateButton("Task2");
			bManagers[i]->deactivateButton("Task3");
			bManagers[i]->deactivateButton("Task4");
			break;
		case UI_E_TO_INTERACT:
			createTextButton(bManagers[i], "EInteract", 58, 25, 12.8, 6.4, 0, 0, Color(1, 1, 1), "Press E to interact", 4);
			bManagers[i]->activateButton("EInteract");
			break;
		}
	}

	setCurrentUI(UI_MAIN_MENU);
}

UIManager::~UIManager()
{
}

void UIManager::Update(Scene* scene, double dt)
{
	bManagers[currentMenu]->Update(scene, dt);
	activeMenus[UI_E_TO_INTERACT] = false;
	if (uiActive == true)
	{
		if (Application::IsKeyPressed('L') && (currentMenu != UI_ITEM_INVENTORY && currentMenu != UI_INTERACTION && currentMenu != UI_MAIN_MENU) && !(currentMenu == UI_ITEM_INVENTORY || currentMenu == UI_WEAPON_INVENTORY || currentMenu == UI_GARAGE_INVENTORY))
		{
			if (nextKeyPress < Game::gElapsedTime) 
			{ //Means can press
				setCurrentUI(UI_ITEM_INVENTORY);
				nextKeyPress = Game::gElapsedTime + 1.0f;
			}
		}
		else if (Application::IsKeyPressed('L') && (currentMenu == UI_ITEM_INVENTORY || currentMenu == UI_WEAPON_INVENTORY || currentMenu == UI_GARAGE_INVENTORY))
		{
			if (nextKeyPress < Game::gElapsedTime) 
			{ //Means can press
				setCurrentUI(UI_GENERAL);
				nextKeyPress = Game::gElapsedTime + 1.0f;
			}
		}
		for (auto& buttonCollide : getCurrentBM()->getButtonsInteracted()) {
			switch (currentMenu) {
			case UI_GENERAL:
				break;
			case UI_ITEM_INVENTORY:
				if (buttonCollide->buttonClicked->getName() == "UIWeaponsInventory" && buttonCollide->justClicked) //Weapons button
				{
					setCurrentUI(UI_WEAPON_INVENTORY);
				}
				if (buttonCollide->buttonClicked->getName() == "UIGarageInventory" && buttonCollide->justClicked) //Garage Button
				{
					setCurrentUI(UI_GARAGE_INVENTORY);
				}
				for (int i = 0; i < ITEM_AMOUNT; i++)
				{
					if (buttonCollide->buttonClicked->getName() == ("UIItemInventorySlot" +std::to_string(i + 1)) && buttonCollide->justHovered) 
					{
						Game::inv.getItemInventory()->setCurrentItem(i);
					}
				}
				break;
			case UI_WEAPON_INVENTORY:
				if (buttonCollide->buttonClicked->getName() == "UIItemsInventory" && buttonCollide->justClicked) //Items button
				{
					setCurrentUI(UI_ITEM_INVENTORY);
				}
				if (buttonCollide->buttonClicked->getName() == "UIGarageInventory" && buttonCollide->justClicked) //Garage Button
				{
					setCurrentUI(UI_GARAGE_INVENTORY);
				}
				if (Game::inv.getWeaponVector().size() > 0)
				{
					for (int i = 0; i < Game::inv.getWeaponVector().size(); i++)
					{
						if (buttonCollide->buttonClicked->getName() == ("UIWeaponInventorySlot" + std::to_string(i + 1)) && buttonCollide->justHovered)
						{
							Game::inv.getWeaponInventory()->setActiveWeapon(Game::inv.getWeaponVector()[i]->getWeaponType());
						}
					}
				}
				break;
			case UI_GARAGE_INVENTORY:
				if (buttonCollide->buttonClicked->getName() == "UIItemsInventory" && buttonCollide->justClicked) //Items button
				{
					setCurrentUI(UI_ITEM_INVENTORY);
				}
				if (buttonCollide->buttonClicked->getName() == "UIWeaponsInventory" && buttonCollide->justClicked) //Weapons button
				{
					setCurrentUI(UI_WEAPON_INVENTORY);
				}
				if (Game::inv.getGarageVector().size() > 0)
				{
					for (int i = 0; i < Game::inv.getGarageVector().size(); i++)
					{
						if (buttonCollide->buttonClicked->getName() == ("UIGarageInventorySlot" + std::to_string(i + 1)) && buttonCollide->justHovered)
						{
							Game::inv.switchCar(Game::inv.getGarageVector()[i]->getCarType());
						}
					}
				}
				break;
			case UI_MAIN_MENU:
				if (buttonCollide->buttonClicked->getName() == "MainMenuPlayButton" && buttonCollide->justClicked)//Main Menu play button
				{
					setCurrentUI(UI_GENERAL);
				}
				break;
			case UI_INTERACTION:
				if (Game::iManager.getQueue().Top()->interactionChoices.empty()) {
					if (buttonCollide->buttonClicked->getName() == "InteractionButton" && buttonCollide->justClicked) {
						Game::iManager.nextInteraction(Game::iManager.getQueue().Top()->nextInteractionKey);
					}
				}
				else {
					for (int i = 0; i < Game::iManager.getQueue().Top()->interactionChoices.size(); ++i) {
						std::stringstream ss;
						ss << "Choice" << i + 1;
						if (buttonCollide->buttonClicked->getName() == ss.str() && buttonCollide->justClicked) {
							for (auto& entry : Game::iManager.getQueue().Top()->interactionChoices[i]->postInteractionCMD) {
								Game::iManager.runCommand(*entry);
							}
							Game::iManager.nextInteraction(Game::iManager.getQueue().Top()->interactionChoices[i]->nextInteractionKey);
							break;
						}
					}
				}
				break;
			}
		}
		if (Game::uiManager.getCurrentMenu() == UI_GENERAL)
		{
			switch (digitCount(Game::cash))
			{
			case 1:
				Game::uiManager.getByTypeBM(UI_GENERAL)->getButtonByName("Cash")->setOrigin(122, 65);
				break;
			case 2:
				Game::uiManager.getByTypeBM(UI_GENERAL)->getButtonByName("Cash")->setOrigin(120, 65);
				break;
			case 3:
				Game::uiManager.getByTypeBM(UI_GENERAL)->getButtonByName("Cash")->setOrigin(118, 65);
				break;
			case 4:
				Game::uiManager.getByTypeBM(UI_GENERAL)->getButtonByName("Cash")->setOrigin(116, 65);
				break;
			case 5:
				Game::uiManager.getByTypeBM(UI_GENERAL)->getButtonByName("Cash")->setOrigin(114, 65);
				break;
			case 6:
				Game::uiManager.getByTypeBM(UI_GENERAL)->getButtonByName("Cash")->setOrigin(112, 65);
				break;
			case 7:
				Game::uiManager.getByTypeBM(UI_GENERAL)->getButtonByName("Cash")->setOrigin(110, 65);
				break;
			}
			Game::uiManager.getByTypeBM(UI_GENERAL)->getButtonByName("Cash")->setText("$" + std::to_string(Game::cash));
		}
	}
}

void UIManager::enableUI()
{
	for (int i = 0; i < bManagers[currentMenu]->getButtons().size(); i++)
	{
		bManagers[currentMenu]->activateButton(bManagers[currentMenu]->getButtons().at(i)->getName());
	}
}

void UIManager::disableUI()
{
	for (int i = 0; i < bManagers[currentMenu]->getButtons().size(); i++)
	{
		bManagers[currentMenu]->deactivateButton(bManagers[currentMenu]->getButtons().at(i)->getName());
	}
}

void UIManager::Render(Scene* scene)
{
	for (int i = 0; i < UI_MENU_COUNT; i++) {
		UI_MENUS type = static_cast<UI_MENUS>(i);
		if (type == currentMenu || activeMenus[type] == true) {
			bManagers[type]->Render(scene);
		}
	}
}

void UIManager::changeTextButton(std::string newText, std::string bName)
{
	this->bManagers[currentMenu]->getButtonByName(bName)->setText(newText);
}

void UIManager::createTextButton(ButtonManager* bManager, std::string buttonName, float originX, float originY, float quadSizeX, float quadSizeY, float offsetX, float offsetY, Color textColour, std::string textString, float textSize)
{
	Button* namedButton;
	namedButton = new Button(buttonName, originX, originY, quadSizeX, quadSizeY, UI_BLANK);
	namedButton->spawnTextObject("Text", textColour, CALIBRI, textSize);
	namedButton->getTextObject()->setTextString(textString);
	namedButton->getTextObject()->setTextOffsetFromTopLeft(offsetX, offsetY);
	bManager->addButton(namedButton);
	bManager->deactivateButton(textString);
}

void UIManager::createNoTextButton(ButtonManager* bManager, std::string buttonName, float originX, float originY, float quadSizeX, float quadSizeY, GEOMETRY_TYPE quadTexture)
{
	Button* noTextButton;
	noTextButton = new Button(buttonName, originX, originY, quadSizeX, quadSizeY, quadTexture);
	bManager->addButton(noTextButton);
	bManager->deactivateButton(buttonName);
}

void UIManager::createButton(ButtonManager* bManager, std::string buttonName, float originX, float originY, float quadSizeX, float quadSizeY, GEOMETRY_TYPE quadTexture, float offsetX, float offsetY, Color textColour, std::string textString, float textSize)
{
	Button* namedButton;
	namedButton = new Button(buttonName, originX, originY, quadSizeX, quadSizeY, quadTexture);
	namedButton->spawnTextObject("Text", textColour, CALIBRI, textSize);
	namedButton->getTextObject()->setTextString(textString);
	namedButton->getTextObject()->setTextOffsetFromTopLeft(offsetX, offsetY);
	bManager->addButton(namedButton);
	bManager->deactivateButton(textString);
}

void UIManager::setUIactive(UI_MENUS ui) {
	this->activeMenus[ui] = true;
}

void UIManager::setCurrentUI(UI_MENUS newUI)
{
	Game::inv.getActiveWeapon()->setUIcooldown(0.5f);
	if (!bManagers[currentMenu]->getButtonsInteracted().empty()) {
		for (auto& entry : bManagers[currentMenu]->getButtonsInteracted()) {
			entry->justClicked = false;
			entry->justHovered = false;
		}
	}
	
	Application::setCursorEnabled(false);
	this->currentMenu = newUI;
	switch (newUI)
	{
	case UI_GENERAL:
		//this->enableUI();
		break;
	case UI_ITEM_INVENTORY:
		Application::setCursorEnabled(true);
		//this->enableUI();
		break;
	case UI_WEAPON_INVENTORY:
		Application::setCursorEnabled(true);
		//this->enableUI();
		break;
	case UI_GARAGE_INVENTORY:
		Application::setCursorEnabled(true);
		//this->enableUI();
		break;
	case UI_MAIN_MENU:
		Application::setCursorEnabled(true);
		break;
	case UI_INTERACTION:
		Application::setCursorEnabled(true);
		break;
	}
}

void UIManager::setCurrentBM(ButtonManager* bManager)
{
	this->bManagers[currentMenu] = bManager;
}

UI_MENUS UIManager::getCurrentMenu()
{
	return this->currentMenu;
}

bool UIManager::getUIActiveBool()
{
	return this->uiActive;
}

ButtonManager* UIManager::getCurrentBM()
{
	return this->bManagers[currentMenu];
}

ButtonManager* UIManager::getByTypeBM(UI_MENUS UI)
{
	return this->bManagers[UI];
}

ButtonManager* UIManager::getbManagerArray(UI_MENUS newUI)
{
	return this->bManagers[newUI];
}
