#pragma once
#include "Entity.h"
#include "Player.h"

/******************************************************************************/
/*!
\file	Car.h
\author Joash Foo
\brief Header file containing a CAR_TYPE enum and the Car class itself.
*/
/******************************************************************************/

enum CAR_TYPE
{
	SEDAN = 0,
	SEDAN_SPORTS,
	RACER,
	POLICE,
	AMBULANCE,
	SUV,
	HATCH_BACK_SPORTS,
	TRACTOR_SHOVEL,
	TRUCK,
	VAN,
	CAR_COUNT,
};

class Player;

/******************************************************************************/
/*!
		Class Car:
\brief Car class for car movement
*/
/******************************************************************************/
class Car : public Entity
{
private:
	GEOMETRY_TYPE associatedType; // associated Mesh for the car
	CAR_TYPE      carType; // type to generate car Mesh and set max speed

	Vector3       velocity;
	Vector3       driftVector;
	
	float         carSpeed; // current car speed
	float		  maxCarSpeed; // max car speed
	float		  acceleration; // acceleration
	float         boostMeter; //boost meter
	bool		  drifting; // is drifting
	bool		  boosting; // is boosting

	Player*		  plr; // pointer to player to check if player is in car.
	
public:
	Car(CAR_TYPE, Scene* ,std::string);
	Car(float, CAR_TYPE);
	Car();
	~Car();

	void     Init(CAR_TYPE type, Scene* scene, std::string name);
	void     setSpeed(float speed);
	void	 setAccel(float a);
	void     setVelocity(Vector3);
	void     setPlayer(Player*);
	float	 getAccel();
	float    getSpeed();
	Vector3  getVelocity();
	static float	 getMaxCarSpeed(CAR_TYPE carType);

	CAR_TYPE getCartype();
	Player*  getPlayer();
	void     Drive(double dt); 
	float    getBoostMeter();

	void     Update(double);
	void     Render();
};
