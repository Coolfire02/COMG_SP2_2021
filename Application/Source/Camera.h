#ifndef CAMERA_H
#define CAMERA_H

#include "Application.h"
#include "Vector3.h"
#include "Mtx44.h"
#include "Entity.h"
#include "Player.h"
#include "Car.h"

enum CAMERATYPE {
	FIRSTPERSON,
	THIRDPERSON,
	TOPDOWN_FIRSTPERSON,
	TOPDOWN_THIRDPERSON
};

class Camera
{
public:
	CAMERATYPE camType;
	Entity*    carPtr;

	Vector3 position, TPSPositionVector;
	Vector3 target, defaultTarget;
	Vector3 up, defaultUp;

	float test_pitch;

	Camera();
	~Camera();
	void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	void Reset();
	void Update(double dt);

	//How much to move in the X,Y,Z coordinates
	void Move(float x, float y, float z); 
};

#endif