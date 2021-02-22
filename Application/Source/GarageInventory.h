#pragma once
#include "Car.h"
//GarageInventory class created by Ridwan on 16/2/2021

class GarageInventory //Garage Slot
{
private:
	CAR_TYPE carType;
public:
	//Initialising
	GarageInventory();
	GarageInventory(CAR_TYPE cartype);
	~GarageInventory();

	//Setter
	void addCar(CAR_TYPE cartype);

	//Getter
	CAR_TYPE getCarType();
};

