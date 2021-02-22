#include "UIManager.h"

UIManager::UIManager()
{
	//bManager = bN;
	currentMenu = MAIN_MENU;
}

UIManager::~UIManager()
{
}

void UIManager::RenderUI()
{
	switch (this->currentMenu)
	{
	case GENERAL_UI:
		/*for (auto& button : bManager->getButtons()) {
			button->Render();
		}*/
		break;
	case ITEM_INVENTORY:
		break;
	case WEAPON_INVENTORY:
		break;
	case GARAGE_INVENTORY:
		break;
	case MAIN_MENU:
		break;
	default:
		break;
	}
}

void UIManager::setCurrentMenu(UI_MENUS newMenu)
{
	this->currentMenu = newMenu;
}

UI_MENUS UIManager::getCurrentMenu()
{
	return this->currentMenu;
}