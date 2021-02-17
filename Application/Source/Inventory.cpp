#include "Inventory.h"

Inventory::Inventory()
{
	currentCar = nullptr;
	currentItem = nullptr;

	//Create garage inventory
	currentCar = new GarageInventory(SEDAN);
	garageInv.push_back(currentCar);

	//Create item inventory
	currentItem = new ItemInventory(EMPTY, 0);
	itemInv.push_back(currentItem);
}

Inventory::~Inventory()
{
}

void Inventory::addCar(CAR_TYPE cartype)
{
	if (garageInv[0] == nullptr) //If player does not have any item yet
	{
		garageInv.clear();
		currentCar = new GarageInventory(cartype);
		garageInv.push_back(currentCar);
	}
	for (int i = 0; i < garageInv.size(); i++) //If player owns car already
	{
		if (garageInv[i]->getCarType() == cartype)
		{
			return;
		}
	}
	GarageInventory* addingCar; //If player does not own a specific car yet
	addingCar = new GarageInventory(cartype);
	garageInv.push_back(addingCar);
}

void Inventory::addItem(ITEM_TYPE itemtype, int amt)
{
	if (itemInv[0] == nullptr) //If player does not have any item yet
	{
		itemInv.clear();
		currentItem = new ItemInventory(itemtype, amt);
		itemInv.push_back(currentItem);
	}
	else
	{
		for (int i = 0; i < itemInv.size(); i++) //If player owns item already
		{
			if (itemInv[i]->getItemType() == itemtype)
			{
				itemInv[i]->setAmtOfItems(itemInv[i]->getAmtOfItems() + amt);
				return;
			}
		}
		
		ItemInventory* addingItem; //If player does not own a specific item yet
		addingItem = new ItemInventory(itemtype, amt);
		itemInv.push_back(addingItem);
	}
}

void Inventory::changeItemAmt(ITEM_TYPE itemtype, int amt)
{
	for (int i = 0; i < itemInv.size(); i++) //If player owns item already
	{
		if (itemInv[i]->getItemType() == itemtype)
		{
			itemInv[i]->setAmtOfItems(itemInv[i]->getAmtOfItems() + amt);
			if (itemInv[i]->getAmtOfItems() > 0)
			{
				//need to fix item inv deletion
			}
			return;
		}
	}
}

void Inventory::deleteItem(ITEM_TYPE itemtype)
{
}

void Inventory::switchCar(CAR_TYPE cartype)
{
	for (int i = 0; i < garageInv.size(); i++)
	{
		if (garageInv[i]->getCarType() == cartype)
		{
			currentCar = garageInv[i];
			return;
		}
	}
}

void Inventory::toggleItem()
{
	for (int i = 0; i < itemInv.size(); i++)
	{
		if (currentItem == itemInv[i])
		{
			if ((i + 1) < itemInv.size()) //Go to next item when not at last slot
			{
				std::cout << "Switch";
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

void Inventory::getGarageInventory()
{
}

void Inventory::getItemInventory()
{
}

CAR_TYPE Inventory::getCurrentCarType()
{
	return currentCar->getCarType();
}

ITEM_TYPE Inventory::getCurrentItemType()
{
	return currentItem->getItemType();
}

int Inventory::getCurrentItemAmt()
{
	return currentItem->getAmtOfItems();
}
