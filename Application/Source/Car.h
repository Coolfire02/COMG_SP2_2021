#pragma once
#include "Entity.h"

enum CAR_TYPE
{

};

class Car : public Entity {
private:
	bool carBought;
	int carType;
public:
	Car();
	~Car();

};

