#ifndef CAMERA_FIRST_PERSON_H
#define CAMERA_FIRST_PERSON_H

#include "Application.h"
#include "Vector3.h"
#include "Mtx44.h"
#include "Entity.h"

class FirstPersonCamera
{
public:
	Vector3 position;
	Vector3 target;
	Vector3 up;

	FirstPersonCamera();
	~FirstPersonCamera();
	void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	void Reset();
	void Update(double dt);

	//How much to move in the X,Y,Z coordinates
	void Move(float x, float y, float z); 
};

#endif