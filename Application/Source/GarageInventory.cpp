#include "GarageInventory.h"

GarageInventory::GarageInventory()
{
	this->carType = SEDAN;
}

GarageInventory::GarageInventory(CAR_TYPE cartype)
{
	this->carType = cartype;
}

GarageInventory::~GarageInventory()
{
}

void GarageInventory::addCar(CAR_TYPE cartype)
{
	this->carType = cartype;
}

CAR_TYPE GarageInventory::getCarType()
{
	return this->carType;
}