#pragma once
#include "Item.h"
#include <vector>
//ItemInventory class created by Ridwan on 16/2/2021

/******************************************************************************/
/*!
\file	ItemInventory.h
\author Ridwan
\brief
Handles items in an Inventory.
*/
/******************************************************************************/


/******************************************************************************/
/*!
		Class ItemInventory:
\brief Handles items in an Inventory.
*/
/******************************************************************************/
class ItemInventory //Inventory slot
{
private:
	std::vector<Item*> itemInv; //Store items
	Item* currentItem; //Currently chosen item in slot
public:
	//Initialising
	ItemInventory();
	ItemInventory(ITEM_TYPE itemtype, int amt);
	~ItemInventory();

	//Add items into inventory and can add and subtract item amount
	void addItem(ITEM_TYPE itemtype, int amt);

	//Toggle through owned items
	void toggleItem();

	//Checks if item has reached 0
	void negativeAmtCheckAndSetter(Item* item, int number);

	//Setters
	void setAmtOfItems(ITEM_TYPE itemtype, int amt);
	void setCurrentItem(int itemType);

	//Getter
	int getCurrentItemAmt();
	ITEM_TYPE getCurrentItemType();
	Item* getCurrentItem();
	std::vector<Item*> getItemVect();
};

