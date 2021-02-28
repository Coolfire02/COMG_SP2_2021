#pragma once
#include "Car.h"
/******************************************************************************/
/*!
\file	GarageInventory.h
\author Ridwan
\brief Header file containing the GarageInventory class.
*/
/******************************************************************************/

/******************************************************************************/
/*!
		Class GarageInventory:
\brief Garage Inventory that manages the the cars.
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

