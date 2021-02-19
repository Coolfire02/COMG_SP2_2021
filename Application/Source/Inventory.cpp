#include "Inventory.h"

Inventory::Inventory()
{
	currentCar = nullptr;
	weaponInv = nullptr;

	//Create garage inventory
	currentCar = new GarageInventory(SEDAN);
	garageInv.push_back(currentCar);

	//For item inventory
	itemInventory = nullptr;
}

Inventory::~Inventory()
{
}

void Inventory::addWeap(WEAPON_TYPE weapontype)
{
	Weapon* temp = new Weapon();
	weaponInv->addWeapon(temp, weapontype);
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
	if (itemInventory == nullptr) //If player does not have any item yet
	{
		itemInventory = new ItemInventory(itemtype, amt);
	}
	else
	{
		itemInventory->addItem(itemtype, amt);
	}
}

void Inventory::changeItemAmt(ITEM_TYPE itemtype, int amt)
{
	if (itemInventory != nullptr)
		itemInventory->setAmtOfItems(itemtype, amt);
	return;
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

void Inventory::switchWeapon(WEAPON_TYPE wType)
{
	weaponInv->setActiveWeapon(wType);
}

void Inventory::toggleItem()
{
	if (itemInventory != nullptr)
		itemInventory->toggleItem();
	return;
}

void Inventory::getGarageInventory()
{
	//blank for now
}

ItemInventory* Inventory::getItemInventory()
{
	return this->itemInventory;
}

std::vector<Item*> Inventory::getItemVector()
{
	return itemInventory->getItemVect();
}

CAR_TYPE Inventory::getCurrentCarType()
{
	return currentCar->getCarType();
}

ITEM_TYPE Inventory::getCurrentItemType()
{
	if (itemInventory != nullptr)
		return itemInventory->getCurrenItemType();
}

int Inventory::getCurrentItemAmt()
{
	if (itemInventory != nullptr)
		return itemInventory->getCurrentItemAmt();
}

Weapon* Inventory::getActiveWeapon()
{
	if (weaponInv == nullptr)
		return nullptr;
	else
		return weaponInv->getActiveWeapon();
}
