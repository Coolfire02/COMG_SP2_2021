#pragma once
#include "GarageInventory.h"
#include "ItemInventory.h"
//Inventory class created by Ridwan on 16/2/2021
//Optimized inventory class by Ridwan on 17/2/2021

class Inventory
{
private:
	std::vector<GarageInventory*> garageInv;
	GarageInventory* currentCar;
	std::vector<ItemInventory*> itemInv;
	ItemInventory* currentItem;
public:
	Inventory();
	~Inventory();

	//Adding Cars/Items
	void addCar(CAR_TYPE cartype);
	void addItem(ITEM_TYPE itemtype, int amt);

	//Changing Item Amount
	void changeItemAmt(ITEM_TYPE itemtype, int amt);
	void deleteItem(ITEM_TYPE itemtype);

	//Switching Cars/Items
	void switchCar(CAR_TYPE cartype);
	void toggleItem();

	//Getters
	void getGarageInventory();
	void getItemInventory();

	CAR_TYPE getCurrentCarType();
	ITEM_TYPE getCurrentItemType();
	int getCurrentItemAmt();
};

