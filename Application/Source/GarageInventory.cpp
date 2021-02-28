#include "GarageInventory.h"
#include <sstream>

/******************************************************************************/
/*!
\brief Initialises the car type.
*/
/******************************************************************************/
GarageInventory::GarageInventory()
{
	this->carType = SEDAN;
}

/******************************************************************************/
/*!
\brief Initialises the car type given a parameter.
*/
/******************************************************************************/
GarageInventory::GarageInventory(CAR_TYPE cartype)
{
	this->carType = cartype;
}

GarageInventory::~GarageInventory()
{
}

/******************************************************************************/
/*!
\brief Adds a car to
*/
/******************************************************************************/
void GarageInventory::addCar(CAR_TYPE cartype)
{
	this->carType = cartype;
}

CAR_TYPE GarageInventory::getCarType()
{
	return this->carType;
}

/******************************************************************************/
/*!
\brief returns the Cars max speed.
*/
/******************************************************************************/
std::string GarageInventory::getMaxCarSpd(CAR_TYPE carType)
{
	int speedToKM = 100;
	std::ostringstream ss;
	ss.precision(4);
	ss << (speedToKM * Car::getMaxCarSpeed(carType));
	std::string var = ss.str();

	return var;
}
