#pragma once
#include "GarageInventory.h"
#include "ItemInventory.h"
#include "WeaponInventory.h"

//Inventory class created by Ridwan on 16/2/2021
//Optimized inventory class by Ridwan on 17/2/2021

/******************************************************************************/
/*!
\file	Inventory.h
\author Ridwan
\brief Header file containing the Inventory class.
*/
/******************************************************************************/

/******************************************************************************/
/*!
		Class Inventory:
\brief Inventory class that manages all necessary inventories such as Weapon Inventory, Item Inventory and Garage Inventory.
*/
/******************************************************************************/
class Inventory
{
private:
	std::vector<GarageInventory*> garageInv; //Store cars player owns
	GarageInventory* currentCar; //Points to current car
	
	ItemInventory* itemInventory; //To get item Inventory
	WeaponInventory* weaponInv;//To get Weapon Inventory
	float toggleTimer;
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
	void deleteWeapon(WEAPON_TYPE wType);

	//Switching Cars/Items/Weapons
	void switchCar(int cartype);
	void switchWeapon(int index);
	void toggleItem();

	//Getters
	GarageInventory* getCurrentCar();
	std::vector<GarageInventory*> getGarageVector();
	std::vector<Weapon*> getWeaponVector();
	ItemInventory* getItemInventory();
	WeaponInventory* getWeaponInventory();
	std::vector<Item*> getItemVector();

	CAR_TYPE getCurrentCarType();
	ITEM_TYPE getCurrentItemType();
	int getCurrentItemAmt();
	Weapon* getActiveWeapon();
	WEAPON_TYPE getCurrentWeaponType();

	void Update(double);
};

