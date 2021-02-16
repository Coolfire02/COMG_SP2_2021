#pragma once
#include "Car.h"
#include <vector>
class GarageInventory
{
private:
	std::vector<Car*> carList;
public:
	GarageInventory();
	~GarageInventory();

	void addCar(float spd, CAR_TYPE cartype);
	bool getCar(CAR_TYPE cartype);
	std::vector<Car*> getCarlist();
};

