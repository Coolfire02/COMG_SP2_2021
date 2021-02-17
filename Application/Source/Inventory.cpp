#include "Inventory.h"

Inventory::Inventory()
{
	//Create garage inventory
	GarageInventory* temp;
	temp = new GarageInventory(NO_CAR);
	garageInv.push_back(temp);

	//Create item inventory
	ItemInventory* addingItem; //If player does not own a specific item yet
	addingItem = new ItemInventory(EMPTY, 0);
	itemInv.push_back(addingItem);
}

Inventory::~Inventory()
{
}

void Inventory::addCar(CAR_TYPE cartype)
{
	if (garageInv[0]->getCarType() == NO_CAR) //If player does not have any car yet
	{
		garageInv.pop_back();
		GarageInventory* temp;
		temp = new GarageInventory(cartype);
		garageInv.push_back(temp);
	}
	else
	{
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
}

void Inventory::addItem(ITEM_TYPE itemtype, int amt)
{
	if (this->itemInv[0]->getItemType() == EMPTY) //If player does not have any item yet
	{
		itemInv.pop_back();
		ItemInventory* temp;
		temp = new ItemInventory(itemtype, amt);
		itemInv.push_back(temp);
	}
	else
	{
		for (int i = 0; i < this->itemInv.size(); i++) //If player owns item already
		{
			if (this->itemInv[i]->getItemType() == itemtype)
			{
				this->itemInv[i]->setAmtOfItems(this->itemInv[i]->getAmtOfItems() + amt);
				return;
			}
		}
		ItemInventory* addingItem; //If player does not own a specific item yet
		addingItem = new ItemInventory(itemtype, amt);
		itemInv.push_back(addingItem);
	}
}

void Inventory::getGarageInventory()
{
}

void Inventory::getItemInventory()
{
}
