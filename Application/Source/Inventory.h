#pragma once
#include "GarageInventory.h"
#include "ItemInventory.h"
class Inventory
{
private:
	GarageInventory* garageInv;
	ItemInventory* itemInv;
public:
	Inventory();
	~Inventory();

	void getGarageInventory();
	void getItemInventory();
};

