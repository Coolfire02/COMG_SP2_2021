#pragma once
#include "Entity.h"
#include "Player.h"
// Car class created by Ridwan on 16/2/21
// Optimized by Joash on 16/2/21

/******************************************************************************/
/*!
		Class Car:
\file	Car.h
\author Joash Foo
\brief
Car class for car movement
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
};

class Player;

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
	bool		  drifting; // is drifting

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

	CAR_TYPE getCartype();
	Player*  getPlayer();
	void     Drive(double dt); 

	void     Update(double);
	void     Render();
};
