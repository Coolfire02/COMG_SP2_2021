#include "FirstPersonCamera.h"

/******************************************************************************/
/*!
\brief
Default constructor
*/
/******************************************************************************/
FirstPersonCamera::FirstPersonCamera()
{

}

/******************************************************************************/
/*!
\brief
Destructor
*/
/******************************************************************************/
FirstPersonCamera::~FirstPersonCamera()
{
}

/******************************************************************************/
/*!
\brief
Initialize FirstPersonCamera

\param pos - position of FirstPersonCamera
\param target - where the FirstPersonCamera is looking at
\param up - up vector of FirstPersonCamera
*/
/******************************************************************************/
void FirstPersonCamera::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = pos;
	this->target = target;
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up).Normalized();
	this->up = right.Cross(view).Normalized();
}



/******************************************************************************/
/*!
\brief
Reset the FirstPersonCamera settings
*/
/******************************************************************************/
void FirstPersonCamera::Reset()
{
}

/******************************************************************************/
/*!
\brief
To be called every frame. FirstPersonCamera will get user inputs and update its position and orientation

\param dt - frame time
*/
/******************************************************************************/
void FirstPersonCamera::Update(double dt)
{
	//if (Application::IsKeyPressed('W')) {
	//	Vector3 view = (target - position).Normalized();
	//	position += view * (float)dt * CAMERA_SPEED * 0.3;
	//	target = position + view;
	//}
	//if (Application::IsKeyPressed('S')) {
	//	Vector3 view = (target - position).Normalized();
	//	position -= view * (float)dt * CAMERA_SPEED * 0.3;
	//	target = position + view;
	//}
	//if (Application::IsKeyPressed('D')) { //Strafing right
	//	Vector3 view = (target - position).Normalized();
	//	Vector3 right = view.Cross(up);
	//	right.y = 0;
	//	right.Normalize();
	//	up = right.Cross(view).Normalized();

	//	position += right * (float)dt * CAMERA_SPEED * 0.3;
	//	target = position + view;
	//}
	//if (Application::IsKeyPressed('A')) { //Strafing left
	//	Vector3 view = (target - position).Normalized();
	//	Vector3 right = view.Cross(up);
	//	right.y = 0;
	//	right.Normalize();
	//	up = right.Cross(view).Normalized();

	//	position -= right * (float)dt * CAMERA_SPEED * 0.3;
	//	target = position + view;
	//}

	static const float CAMERA_SPEED = 45.f;
	static const float ZOOM_SPEED = 20.f;

	if (Application::IsKeyPressed(VK_UP)) { //KEYUP
		float pitch = CAMERA_SPEED * static_cast<float>(dt);
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();
		Mtx44 rotation;
		rotation.SetToRotation(pitch, right.x, right.y, right.z);

		view = rotation * view;
		target = position + view;
	}
	if (Application::IsKeyPressed(VK_LEFT)) {
		float yaw = CAMERA_SPEED * static_cast<float>(dt);
		Vector3 view = (target - position).Normalized();
		Mtx44 rotation;
		rotation.SetToRotation(yaw, 0, 1, 0);
		view = rotation * view;
		target = position + view;
		up = rotation * up;
	}
	if (Application::IsKeyPressed(VK_RIGHT)) {
		float yaw = -CAMERA_SPEED * static_cast<float>(dt);
		Vector3 view = (target - position).Normalized();
		Mtx44 rotation;
		rotation.SetToRotation(yaw, 0, 1, 0);
		view = rotation * view;
		target = position + view;
		up = rotation * up;
	}
	if (Application::IsKeyPressed(VK_DOWN)) {
		float pitch = -CAMERA_SPEED * static_cast<float>(dt);
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();
		Mtx44 rotation;
		rotation.SetToRotation(pitch, right.x, right.y, right.z);
		view = rotation * view;
		target = position + view;
	}




}

void FirstPersonCamera::Move(float x, float y, float z) {
	Vector3 view = (target - position).Normalized();
	position.x += x;
	position.y += y;
	position.z += z;
	target = position + view;
	
}