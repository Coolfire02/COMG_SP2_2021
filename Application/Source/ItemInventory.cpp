#include "ItemInventory.h"

ItemInventory::ItemInventory()
{
	currentItem = nullptr;

	
}

ItemInventory::ItemInventory(ITEM_TYPE itemtype, int amt)
{
	currentItem = new Item(itemtype, amt);
	itemInv.push_back(currentItem);
}

ItemInventory::~ItemInventory()
{
	//blank on purpose
}

void ItemInventory::addItem(ITEM_TYPE itemtype, int amt)
{
	if (itemInv[0] == nullptr) //If player does not have any item yet
	{
		currentItem = new Item(itemtype, amt);
		itemInv.push_back(currentItem);
	}
	else
	{
		for (int i = 0; i < itemInv.size(); i++) //If player owns item already
		{
			if (itemInv[i]->getType() == itemtype)
			{
				negativeAmtCheckAndSetter(itemInv[i], amt);
				return;
			}
		}

		Item* addingItem; //If player does not own a specific item yet
		addingItem = new Item(itemtype, amt);
		itemInv.push_back(addingItem);
	}
}

void ItemInventory::toggleItem()
{
	for (int i = 0; i < itemInv.size(); i++)
	{
		if (currentItem == itemInv[i])
		{
			if ((i + 1) < itemInv.size()) //Go to next item when not at last slot
			{
				currentItem = itemInv[i + 1];
			}
			else //If item is at last slot then go to first slot
			{
				currentItem = itemInv[0];
			}
			return;
		}
	}
}

void ItemInventory::usingItem()
{
	for (int i = 0; i < itemInv.size(); i++)
	{
		if (itemInv[i]->getType() == currentItem->getType())
		{
			itemInv[i]->setAmt(itemInv[i]->getAmt() - 1);
			return;
		}
	}
}

void ItemInventory::negativeAmtCheckAndSetter(Item* item, int number)
{
	if (item == nullptr)
		return;
	if ((item->getAmt() + number) <= 0)
		item->setAmt(0);
	else
		item->setAmt(item->getAmt() + number);
}

void ItemInventory::setAmtOfItems(ITEM_TYPE itemtype, int amt)
{
	for (int i = 0; i < itemInv.size(); i++) //If player owns item already
	{
		if (itemInv[i]->getType() == itemtype)
		{
			negativeAmtCheckAndSetter(itemInv[i], amt);
			return;
		}
	}
}

int ItemInventory::getCurrentItemAmt()
{
	return this->currentItem->getAmt();
}

ITEM_TYPE ItemInventory::getCurrenItemType()
{
	return this->currentItem->getType();
}

Item* ItemInventory::getCurrentItem()
{
	return this->currentItem;
}


