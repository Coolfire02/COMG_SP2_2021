#ifndef CAMERA_H
#define CAMERA_H

#include "Application.h"
#include "Vector3.h"
#include "Mtx44.h"
#include "Entity.h"
#include "Player.h"
#include "Car.h"

/******************************************************************************/
/*!
\brief
enum to check for Camera Type.
*/
/******************************************************************************/
enum CAMERATYPE {
	FIRSTPERSON,
	THIRDPERSON,
	TOPDOWN_FIRSTPERSON,
	TOPDOWN_THIRDPERSON,
	TOPDOWN_MAINMENU
};

/******************************************************************************/
/*!
\file	Camera.h
\author Joash Foo
\author Jordan Low
\brief
Camera System for our game.

Includes the Third Person Camera, Top Down Camera and First Person Camera functionalities.
Includes Mouse Movement and takes into account Player's position in a scene.
*/
/******************************************************************************/

/******************************************************************************/
/*!
		Class Camera:
\brief Camera System for our game.
*/
/******************************************************************************/
class Camera
{
public:
	CAMERATYPE camType;
	Entity*	   playerPtr;

	Vector3 position, TPSPositionVector; // TPS Vector used for third person camera's position around the target.
	Vector3 target, defaultTarget;
	Vector3 up, defaultUp;

	float yaw; // x displacement of the mouse from the center of the window
	float pitch; // y displacement of the mouse from the center of the window
	float additionalYaw;
	float total_pitch; 
	float total_yaw;

	Camera();
	~Camera();
	void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	void Reset();
	void Update(double dt);
	bool isLookingAt(Vector3 pos);

	//How much to move in the X,Y,Z coordinates
	void Move(float x, float y, float z); 
};

#endif