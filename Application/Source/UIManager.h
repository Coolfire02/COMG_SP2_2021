#pragma once
#include "ButtonManager.h"

enum UI_MENUS
{
	GENERAL_UI = 0, //renders hp,weapons,item
	ITEM_INVENTORY, //renders items owned and can click weapons and cars button
	WEAPON_INVENTORY, //render weapons owned and can click items and cars button
	GARAGE_INVENTORY, //renders cars owned and can click items and weapons button
	MAIN_MENU, //renders title screen
	MENU_COUNT,
};

class UIManager
{
private:
	/*m_width = 1280;
	m_height = 720;*/ //screen size
	ButtonManager* bManagers[MENU_COUNT]; //Init buttons inside this class
	UI_MENUS currentMenu;
public:
	UIManager();
	~UIManager();

	void RenderUI();

	//Setter
	void setCurrentMenu(UI_MENUS newMenu);

	//Getter
	UI_MENUS getCurrentMenu();
};