#include "ItemInventory.h"

ItemInventory::ItemInventory()
{
	this->item = EMPTY;
	this->amtOfItems = 0;
}

ItemInventory::ItemInventory(ITEM_TYPE itemtype, int amt)
{
	this->item = itemtype;
	this->amtOfItems = amt;
}

ItemInventory::~ItemInventory()
{
	//blank on purpose
}

void ItemInventory::setItemType(ITEM_TYPE itemtype)
{
	this->item = itemtype;
}

void ItemInventory::setAmtOfItems(int amt)
{
	this->amtOfItems = amt;
}

ITEM_TYPE ItemInventory::getItemType()
{
	return this->item.getType();
}

int ItemInventory::getAmtOfItems()
{
	return this->amtOfItems;
}
