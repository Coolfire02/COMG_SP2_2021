#pragma once
#include "Entity.h"
#include "Player.h"
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
	Vector3       velocity;

	float         carSpeed;
	Player*       plr;
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

	Vector3 Interpolate(Vector3, Vector3, double);
	CAR_TYPE getCartype();

	void Update(double);
	void Render();
};

