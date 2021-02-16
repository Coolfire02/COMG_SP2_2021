#include "ItemInventory.h"

ItemInventory::ItemInventory()
{
}

ItemInventory::~ItemInventory()
{
}

void ItemInventory::addItem(ITEM_TYPE itemtype)
{
	Item* temp;
	temp = new Item(itemtype);
	itemList.push_back(temp);
}

//bool ItemInventory::getItem(ITEM_TYPE itemtype)
//{
//	return false;
//}

std::vector<Item*> ItemInventory::getItemlist()
{
	return this->itemList;
}
