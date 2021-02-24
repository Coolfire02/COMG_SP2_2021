#include "UIManager.h"
#include "Application.h"

UIManager::UIManager()
{
}

void UIManager::Init() {
	////bManager = bN;
	currentMenu = UI_MAIN_MENU;
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

			//Weapons UI
			//need to create text buttons for amount
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
			createButton(bManagers[i], "InteractionButton", 64, 13.7, 128, 27.4, UI_TEXTBOX, 3, 12, Color(0, 1, 0), "", 5.0f);
			createButton(bManagers[i], "UIHealth", 40, 5, 40, 5, UI_BLUE, 1, 1, Color(0, 1, 0), "Test", 1.0f);
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
				if (buttonCollide->buttonClicked->getName() == "InteractionButton" && buttonCollide->justClicked) {
					Game::iManager.nextInteraction();
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
	bManagers[currentMenu]->Render(scene);
}

void UIManager::changeTextButton(std::string newText, std::string bName)
{
	this->bManagers[currentMenu]->getButtonByName(bName)->setText(newText);
}

void UIManager::createTextButton(ButtonManager* bManager, std::string buttonName, float originX, float originY, float quadSizeX, float quadSizeY, float offsetX, float offsetY, Color textColour, std::string textString, float textSize)
{
	Button* namedButton;
	namedButton = new Button(textString, originX, originY, quadSizeX, quadSizeY, UI_BLANK);
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
		this->enableUI();
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
