#pragma once
#include "Item.h"
#include <vector>
//ItemInventory class created by Ridwan on 16/2/2021

class ItemInventory //Inventory slot
{
private:
	//int amtOfItems;
	std::vector<Item*> itemInv;
	Item* currentItem;
public:
	ItemInventory();
	ItemInventory(ITEM_TYPE itemtype, int amt);
	~ItemInventory();

	void addItem(ITEM_TYPE itemtype, int amt);
	void toggleItem();
	void usingItem();
	void negativeAmtCheckAndSetter(Item* item, int number);

	//Setters
	void setAmtOfItems(ITEM_TYPE itemtype, int amt);

	//Getter
	int getCurrentItemAmt();
	ITEM_TYPE getCurrenItemType();
	Item* getCurrentItem();
};

