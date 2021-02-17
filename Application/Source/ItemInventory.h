#pragma once
#include "Item.h"
//ItemInventory class created by Ridwan on 16/2/2021

class ItemInventory //Inventory slot
{
private:
	Item item;
	int amtOfItems;
public:
	ItemInventory();
	ItemInventory(ITEM_TYPE itemtype, int amt);
	~ItemInventory();

	//void addItem(ITEM_TYPE itemtype, int amt);

	//Setters
	void setItemType(ITEM_TYPE itemtype);
	void setAmtOfItems(int amt);

	//Getters
	ITEM_TYPE getItemType();
	int getAmtOfItems();
};

