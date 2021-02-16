#pragma once
#include "Entity.h"

enum CAR_TYPE
{
	SEDAN = 0,
	SEDAN_SPORTS,
	RACER,
	POLICE,
	AMBULANCE,
	SUV,
};

class Car : public Entity
{
private:
	float carSpeed;
	bool carBought;
	CAR_TYPE carType;
public:
	Car(float speed, CAR_TYPE type);
	~Car();

	//Setter
	void setSpeed(float speed);
	void setBought(bool bought);

	//Getter
	float getSpeed();
	bool getBought();
	CAR_TYPE getCartype();
};

