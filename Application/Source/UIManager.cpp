#include "UIManager.h"
#include "Application.h"

UIManager::UIManager()
{
}

void UIManager::Init() {
	////bManager = bN;
	currentMenu = UI_MAIN_MENU;
	activeMenus[UI_MISSION] = true; //UI_MISSION Overlay
	uiActive = true;

	for (int i = 0; i < UI_MENU_COUNT; i++)
	{
		bManagers[i] = new ButtonManager();
		switch (i)
		{
		case UI_GENERAL:
			//Items UI
			//need to create text buttons for amount
			createNoTextButton(bManagers[i], "UIItem", 120, 20, 10, 10, UI_EMPTY);
			createNoTextButton(bManagers[i], "UIItemCurrent", 120, 20, 11, 11, UI_BLUE);

			//Weapons UI 128 72
			//need to create text buttons for amount
			createTextButton(bManagers[i], "AmmoCount", 85.5, 8, 1,1, 0,0, Color(1,1,1), "0/0 Ammo", 5.0f);
			createTextButton(bManagers[i], "TotalAmmoCount", 92.25, 5, 1,1, 0,0, Color(1,0,1), "0", 3.0f);
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
			break;
		case UI_ITEM_INVENTORY:
			createNoTextButton(bManagers[i], "UIInventoryBackground", 64, 36, 100, 48, UI_WINDOW);
			createButton(bManagers[i], "UIItemsInventoryBlank", 21.5, 63, 15, 5, UI_WINDOW, 2, 5, Color(1, 0.3, 0.3), "Item", 1.0f);
			createButton(bManagers[i], "UIWeaponsInventory", 36.5, 63, 15, 5, UI_WINDOW, 2, 5, Color(1, 0.3, 0.3), "Guns", 1.0f);
			createButton(bManagers[i], "UIGarageInventory", 51.5, 63, 15, 5, UI_WINDOW, 2, 5, Color(1, 0.3, 0.3), "Cars", 1.0f);
			break;
		case UI_WEAPON_INVENTORY:
			createNoTextButton(bManagers[i], "UIInventoryBackground", 64, 36, 100, 48, UI_WINDOW);
			createButton(bManagers[i], "UIItemsInventory", 21.5, 63, 15, 5, UI_WINDOW, 2, 5, Color(1, 0.3, 0.3), "Item", 1.0f);
			createButton(bManagers[i], "UIWeaponsInventoryBlank", 36.5, 63, 15, 5, UI_WINDOW, 2, 5, Color(1, 0.3, 0.3), "Guns", 1.0f);
			createButton(bManagers[i], "UIGarageInventory", 51.5, 63, 15, 5, UI_WINDOW, 2, 5, Color(1, 0.3, 0.3), "Cars", 1.0f);
			break;
		case UI_GARAGE_INVENTORY:
			createNoTextButton(bManagers[i], "UIInventoryBackground", 64, 36, 100, 48, UI_WINDOW);
			createButton(bManagers[i], "UIItemsInventory", 21.5, 63, 15, 5, UI_WINDOW, 2, 5, Color(1, 0.3, 0.3), "Item", 1.0f);
			createButton(bManagers[i], "UIWeaponsInventory", 36.5, 63, 15, 5, UI_WINDOW, 2, 5, Color(1, 0.3, 0.3), "Guns", 1.0f);
			createButton(bManagers[i], "UIGarageInventoryBlank", 51.5, 63, 15, 5, UI_WINDOW, 2, 5, Color(1, 0.3, 0.3), "Cars", 1.0f);
			break;
		case UI_MAIN_MENU:
			createNoTextButton(bManagers[i], "TitleBackground", 64, 36, 128, 72, TITLE_BG);
			createNoTextButton(bManagers[i], "MainMenuPlayButton", 64, 36, 16, 12, PLAY_BUTTON);
			bManagers[currentMenu] = bManagers[i];
			enableUI();
			break;
		case UI_INTERACTION:
			createButton(bManagers[i], "Choice1", 96, 33.7, 58, 7.4, UI_CHOICE, 9, 5.5, Color(1, 1, 1), "", 3.5f);
			createButton(bManagers[i], "Choice2", 96, 43.8, 58, 7.4, UI_CHOICE, 9, 5.5, Color(1, 1, 1), "", 3.5f);
			createButton(bManagers[i], "Choice3", 96, 53.5, 58, 7.4, UI_CHOICE, 9, 5.5, Color(1, 1, 1), "", 3.5f);
			createButton(bManagers[i], "Choice4", 96, 63.2, 58, 7.4, UI_CHOICE, 9, 5.5, Color(1, 1, 1), "", 3.5f);


			createButton(bManagers[i], "InteractionButton", 64, 13.7, 128, 27.4, UI_TEXTBOX, 3, 12, Color(1, 1, 1), "", 5.0f);
			createButton(bManagers[i], "UIHealth", 40, 5, 40, 5, UI_BLUE, 1, 1, Color(0, 1, 0), "Test", 1.0f);
			break;
		case UI_MISSION:
			createButton(bManagers[i], "MissionComplete", 64, 60, 96, 18, GEO_MISSION_COMPLETE, 20, 7, Color(0.1f, 0.7f, 0.12f), "Test Mission Complete", 4.0f);
			bManagers[i]->deactivateButton("MissionComplete");
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
	if (uiActive == true)
	{
		for (auto& buttonCollide : getCurrentBM()->getButtonsInteracted()) {
			switch (currentMenu) {
			case UI_GENERAL:
				//switchUI(UI_MENUS newMenu)
				enableUI();
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
							Game::iManager.nextInteraction(Game::iManager.getQueue().Top()->interactionChoices[i]->nextInteractionKey);
							break;
						}
					}
				}
				break;
			}
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

void UIManager::setCurrentUI(UI_MENUS newUI)
{
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
