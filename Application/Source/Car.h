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

class Player;

class Car : public Entity
{
private:
	GEOMETRY_TYPE associatedType;
	CAR_TYPE      carType;

	Vector3       velocity;
	Vector3		  velocityGoal;
	Vector3       driftVector;
	Vector3       bounceVector;
	
	float         carSpeed;
	float		  maxCarSpeed;
	float		  acceleration;
	float         driftFalloff;
	bool		  drifting;

	Player*		  plr;
	
public:
	Car(CAR_TYPE, Scene* ,std::string);
	Car(float, CAR_TYPE);
	Car();
	~Car();
	void     Init();
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
