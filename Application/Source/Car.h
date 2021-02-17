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

<<<<<<< Updated upstream
class Player;

class Car : public Entity {
private:
=======
class Car : public Entity
{
private:
	Vector3       velocity;
	bool seated;
	float         carSpeed;
	Player*       plr;
	CAR_TYPE      carType;
>>>>>>> Stashed changes
	GEOMETRY_TYPE associatedType;
	CAR_TYPE      carType;
	Player*       plr;

	Vector3       velocity;
	Vector3		  velocityGoal;
	float		  rotation;
	float         carSpeed;
	float		  carSpeedGoal;
	float		  maxCarSpeed;
	
public:
	Car(CAR_TYPE, Scene* ,std::string);
	Car(float, CAR_TYPE);
	Car();
	~Car();
	 
	void     Init();
	void     setSpeed(float speed);
	void     setPlayer(Player*);
	float    getSpeed();

	float  Interpolate(float, float, double);
	CAR_TYPE getCartype();
	Player* getPlayer();

	void Update(double);
	void Render();
};

