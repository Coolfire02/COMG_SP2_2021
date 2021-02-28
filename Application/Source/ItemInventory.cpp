#include "ItemInventory.h"

/******************************************************************************/
/*!
\brief
Initialise ItemInventory to nullptr
*/
/******************************************************************************/
ItemInventory::ItemInventory()
{
	currentItem = nullptr;
}

/******************************************************************************/
/*!
\brief
Initialise ItemInventory while also adding an item
*/
/******************************************************************************/

ItemInventory::ItemInventory(ITEM_TYPE itemtype, int amt)
{
	currentItem = new Item(itemtype, amt);
	itemInv.push_back(currentItem);
}

ItemInventory::~ItemInventory()
{
	//blank on purpose
}

/******************************************************************************/
/*!
\brief
Add Items based on Item Type as well as amount and can deduct amount through vectors
*/
/******************************************************************************/

void ItemInventory::addItem(ITEM_TYPE itemtype, int amt)
{
	if (itemInv.empty()) //If player does not have any item yet
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
		currentItem = addingItem;
	}
}

/******************************************************************************/
/*!
\brief
Switch to the next item on the vector
*/
/******************************************************************************/

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

/******************************************************************************/
/*!
\brief
Check if item becomes subtracts below 0
*/
/******************************************************************************/

void ItemInventory::negativeAmtCheckAndSetter(Item* item, int number)
{
	if (item == nullptr)
		return;
	if ((item->getAmt() + number) <= 0)
		item->setAmt(0);
	else
		item->setAmt(item->getAmt() + number);
}

/******************************************************************************/
/*!
\brief
Add amount of items based on specific Item Type
*/
/******************************************************************************/

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

/******************************************************************************/
/*!
\brief
Set current Item based on Item Type Enum
*/
/******************************************************************************/

void ItemInventory::setCurrentItem(int itemType)
{
	for (int i = 0; i < itemInv.size(); i++)
	{
		if (itemInv[i]->getType() == itemType)
			this->currentItem = itemInv[i];
	}
}

/******************************************************************************/
/*!
\brief
Get current Item Amount
*/
/******************************************************************************/

int ItemInventory::getCurrentItemAmt()
{
	return this->currentItem->getAmt();
}

/******************************************************************************/
/*!
\brief
Get current Item Type
*/
/******************************************************************************/

ITEM_TYPE ItemInventory::getCurrentItemType()
{
	if (this->currentItem != nullptr)
		return this->currentItem->getType();
}

/******************************************************************************/
/*!
\brief
Get current Item Pointer
*/
/******************************************************************************/

Item* ItemInventory::getCurrentItem()
{
	return this->currentItem;
}

/******************************************************************************/
/*!
\brief
Get current Item List Vector
*/
/******************************************************************************/

std::vector<Item*> ItemInventory::getItemVect()
{
	return this->itemInv;
}


