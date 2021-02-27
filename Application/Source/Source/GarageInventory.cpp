#include "GarageInventory.h"
#include <sstream>

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

std::string GarageInventory::getMaxCarSpd(CAR_TYPE carType)
{
	int speedToKM = 100;
	std::ostringstream ss;
	ss.precision(4);
	ss << (speedToKM * Car::getMaxCarSpeed(carType));
	std::string var = ss.str();

	return var;
}
