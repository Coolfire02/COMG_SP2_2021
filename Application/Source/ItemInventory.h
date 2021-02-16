#pragma once
#include "Item.h"
#include <vector>

class ItemInventory
{
private:
	std::vector<Item*> itemList;
public:
	ItemInventory();
	~ItemInventory();

	void addItem(ITEM_TYPE itemtype);
	//bool getItem(ITEM_TYPE itemtype);
	std::vector<Item*> getItemlist();
};

