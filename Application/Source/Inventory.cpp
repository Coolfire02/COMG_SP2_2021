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
	if (weaponInv == nullptr) //If there are no weapons in the inventory
	{
		Weapon* temp = new Weapon();
		weaponInv = new WeaponInventory(temp, weapontype);
	}
	else
	{
		Weapon* temp = new Weapon();
		weaponInv->addWeapon(temp, weapontype);
	}
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
	//if (itemInv[0] == nullptr) //If player does not have any item yet
	//{
	//	itemInv.clear();
	//	currentItem = new ItemInventory(itemtype, amt);
	//	itemInv.push_back(currentItem);
	//}
	//else
	//{
	//	for (int i = 0; i < itemInv.size(); i++) //If player owns item already
	//	{
	//		if (itemInv[i]->getItemType() == itemtype)
	//		{
	//			itemInv[i]->setAmtOfItems(itemInv[i]->getAmtOfItems() + amt);
	//			return;
	//		}
	//	}
	//	
	//	ItemInventory* addingItem; //If player does not own a specific item yet
	//	addingItem = new ItemInventory(itemtype, amt);
	//	itemInv.push_back(addingItem);
	//}
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
	//for (int i = 0; i < itemInv.size(); i++) //If player owns item already
	//{
	//	if (itemInv[i]->getItemType() == itemtype)
	//	{
	//		itemInv[i]->setAmtOfItems(itemInv[i]->getAmtOfItems() + amt);
	//		if (itemInv[i]->getAmtOfItems() > 0)
	//		{
	//			//need to fix item inv deletion
	//		}
	//		return;
	//	}
	//}
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

void Inventory::switchWeapon(WEAPON_TYPE wType)
{
	weaponInv->setActiveWeapon(wType);
}

void Inventory::toggleItem()
{
	//for (int i = 0; i < itemInv.size(); i++)
	//{
	//	if (currentItem == itemInv[i])
	//	{
	//		if ((i + 1) < itemInv.size()) //Go to next item when not at last slot
	//		{
	//			std::cout << "Switch";
	//			currentItem = itemInv[i + 1];
	//		}
	//		else //If item is at last slot then go to first slot
	//		{
	//			currentItem = itemInv[0];
	//		}
	//		return;
	//	}
	//}
	if (itemInventory != nullptr)
		itemInventory->toggleItem();
	return;
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
