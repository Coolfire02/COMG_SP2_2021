#include "GarageInventory.h"

GarageInventory::GarageInventory()
{
}

GarageInventory::~GarageInventory()
{
}

void GarageInventory::addCar(float spd, CAR_TYPE cartype)
{
	Car* temp;
	temp = new Car(spd, cartype);
	carList.push_back(temp);
}

bool GarageInventory::getCar(CAR_TYPE cartype)
{
	for (int i = 0; i < carList.size(); i++)
	{
		if (carList[i]->getCartype() == cartype)
		{
			return carList[i]->getBought();
		}
	}
}

std::vector<Car*> GarageInventory::getCarlist()
{
	return this->carList;
}
