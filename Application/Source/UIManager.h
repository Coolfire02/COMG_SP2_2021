#pragma once
#include "ButtonManager.h"
#include "Inventory.h"

class Game;

enum UI_MENUS
{
	UI_GENERAL = 0, //renders hp,weapons,item
	UI_ITEM_INVENTORY, //renders items owned and can click weapons and cars button
	UI_WEAPON_INVENTORY, //render weapons owned and can click items and cars button
	UI_GARAGE_INVENTORY, //renders cars owned and can click items and weapons button
	UI_MAIN_MENU, //renders title screen
	UI_INTERACTION,
	UI_MENU_COUNT,
};

class UIManager
{
private:
	/*m_width = 1280;
	m_height = 720;*/ //screen size
	ButtonManager* bManagers[UI_MENU_COUNT]; //Init buttons inside this class


	bool uiActive;
	UI_MENUS currentMenu;
public:
	UIManager();
	~UIManager();

	void Update(Scene* scene, double dt);
	void enableUI();
	void disableUI();

	void Render(Scene* scene);

	void changeTextButton(std::string newText, std::string bName);
	void createTextButton(ButtonManager* bManager, std::string buttonName, float originX, float originY, float quadSizeX, float quadSizeY, float offsetX, float offsetY, Color textColour, std::string textString);
	void createNoTextButton(ButtonManager* bManager, std::string buttonName, float originX, float originY, float quadSizeX, float quadSizeY, GEOMETRY_TYPE quadTexture);
	void createButton(ButtonManager* bManager, std::string buttonName, float originX, float originY, float quadSizeX, float quadSizeY, GEOMETRY_TYPE quadTexture, float offsetX, float offsetY, Color textColour, std::string textString);
	
	//Setter
	void setCurrentUI(UI_MENUS newUI);
	void setCurrentBM(ButtonManager* bManager);

	//Getter
	UI_MENUS getCurrentMenu();
	bool getUIActiveBool();
	ButtonManager* getCurrentBM();
	ButtonManager* getByTypeBM(UI_MENUS UI);
	ButtonManager* getbManagerArray(UI_MENUS newUI);

};