#include "Inventory.h"

Inventory::Inventory()
{
	garageInv = new GarageInventory();
	itemInv = new ItemInventory();
}

Inventory::~Inventory()
{
}
