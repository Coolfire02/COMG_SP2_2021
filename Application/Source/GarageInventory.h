#pragma once
#include "Car.h"
#include <vector>
class GarageInventory //Garage Slot
{
private:
	CAR_TYPE carType;
public:
	GarageInventory();
	GarageInventory(CAR_TYPE cartype);
	~GarageInventory();

	void addCar(CAR_TYPE cartype);
	CAR_TYPE getCarType();
};

