#pragma once
#include "GarageInventory.h"
#include "ItemInventory.h"
//Inventory class created by Ridwan on 16/2/2021

class Inventory
{
private:
	std::vector<GarageInventory*> garageInv;
	std::vector<ItemInventory*> itemInv;
public:
	Inventory();
	~Inventory();

	//Adding Cars/Items
	void addCar(CAR_TYPE cartype);
	void addItem(ITEM_TYPE itemtype, int amt);

	//Getters
	void getGarageInventory();
	void getItemInventory();
};

