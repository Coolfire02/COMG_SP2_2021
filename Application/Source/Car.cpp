#include "Car.h"

Car::Car(float speed, CAR_TYPE type)
{
	this->carSpeed = speed;
	this->carType = type;
	this->carBought = false;
}

Car::~Car()
{
}

void Car::setSpeed(float speed)
{
	this->carSpeed = speed;
}

void Car::setBought(bool bought)
{
	this->carBought = bought;
}

float Car::getSpeed()
{
	return this->carSpeed;
}

bool Car::getBought()
{
	return this->carBought;
}

CAR_TYPE Car::getCartype()
{
	return this->carType;
}
