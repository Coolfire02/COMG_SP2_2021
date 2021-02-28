#pragma once
#include "Car.h"
/******************************************************************************/
/*!
\file	GarageInventory.h
\author Ridwan
\brief
Manages all Vehicles in a Player's Garage Inventory.
*/
/******************************************************************************/

/******************************************************************************/
/*!
		Class GarageInventory:
\brief Manages all Vehicles in a Player's Garage Inventory.
*/
/******************************************************************************/
class GarageInventory //Garage Slot
{
private:
	CAR_TYPE carType; // current car type.
public:
	//Initialising
	GarageInventory();
	GarageInventory(CAR_TYPE cartype);
	~GarageInventory();

	//Setter
	void addCar(CAR_TYPE cartype);

	//Getter
	CAR_TYPE getCarType();
	std::string getMaxCarSpd(CAR_TYPE carType);
};

