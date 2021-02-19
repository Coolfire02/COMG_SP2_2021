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
	float         carSpeed;
	Player*       plr;
	CAR_TYPE      carType;
	GEOMETRY_TYPE associatedType;

	Vector3       velocity;
	Vector3		  velocityGoal;
	Vector3       driftVector;
	float		  acceleration;
	float		  carSpeedGoal;
	float		  maxCarSpeed;
	bool		  drifting;
	
public:
	Car(CAR_TYPE, Scene* ,std::string);
	Car(float, CAR_TYPE);
	Car();
	~Car();
	 
	void     Init();
	void     setSpeed(float speed);
	void	 setAccel(float a);
	void     setPlayer(Player*);
	float	 getAccel();
	float    getSpeed();
	Vector3  getVelocity();

	CAR_TYPE getCartype();
	Player* getPlayer();
	void Drive(double dt);

	void Update(double);
	void Render();
};

