#pragma once
#include "GarageInventory.h"
#include "ItemInventory.h"
#include "WeaponInventory.h"
//Inventory class created by Ridwan on 16/2/2021
//Optimized inventory class by Ridwan on 17/2/2021

class Inventory
{
private:
	std::vector<GarageInventory*> garageInv;
	GarageInventory* currentCar;
	
	ItemInventory* itemInventory;

	WeaponInventory* weaponInv;
public:
	Inventory();
	~Inventory();

	//Adding Cars/Items/Weapons
	void addWeap(WEAPON_TYPE weapontype);
	void addCar(CAR_TYPE cartype);
	void addItem(ITEM_TYPE itemtype, int amt);

	//Changing Item Amount
	void changeItemAmt(ITEM_TYPE itemtype, int amt);
	void deleteItem(ITEM_TYPE itemtype);

	//Switching Cars/Items/Weapons
	void switchCar(CAR_TYPE cartype);
	void switchWeapon(WEAPON_TYPE wType);
	void toggleItem();

	//Getters
	void getGarageInventory();
	void getItemInventory();

	CAR_TYPE getCurrentCarType();
	ITEM_TYPE getCurrentItemType();
	int getCurrentItemAmt();
	Weapon* getActiveWeapon();
};

