#pragma once
#include "Entity.h"
// Car class created by Ridwan on 16/2/21
// Optimized by Joash on 16/2/21

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
	bool          seated;
	float         carSpeed;
	CAR_TYPE      carType;
	GEOMETRY_TYPE associatedType;

public:
	Car(CAR_TYPE type, Scene* scene, std::string);
	Car();
	Car(float speed, CAR_TYPE type);
	~Car();
	 
	void     Init();
	void     setSpeed(float speed);
	float    getSpeed();
	CAR_TYPE getCartype();

	void Update(double);
	void Render();
};

