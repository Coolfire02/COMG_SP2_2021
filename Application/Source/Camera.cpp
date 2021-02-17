#include "Camera.h"
// FPS Camera with mouse input - Joash 16/2/21

/******************************************************************************/
/*!
\brief
Default constructor
*/
/******************************************************************************/
Camera::Camera()
{

}

/******************************************************************************/
/*!
\brief
Destructor
*/
/******************************************************************************/
Camera::~Camera()
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
void Camera::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	camType = FIRSTPERSON;
	this->position = pos;	
	this->TPSPositionVector = Vector3(0, 7, -15);
	this->target = target;
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up).Normalized();
	this->up = right.Cross(view).Normalized();
	test_pitch = 0;
}



/******************************************************************************/
/*!
\brief
Reset the FirstPersonCamera settings
*/
/******************************************************************************/
void Camera::Reset()
{
}

/******************************************************************************/
/*!
\brief
To be called every frame. FirstPersonCamera will get user inputs and update its position and orientation

\param dt - frame time
*/
/******************************************************************************/
void Camera::Update(double dt)
{

	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	static const float CAMERA_SPEED = 100.f;

	switch (camType) {
	case FIRSTPERSON:
		if (Application::IsKeyPressed(VK_LEFT))
		{
			Vector3 view = (target - position).Normalized();
			float yaw = (float)(CAMERA_SPEED * (float)dt);
			Mtx44 rotation;
			rotation.SetToRotation(yaw, 0, 1, 0);
			view = rotation * view;
			target = position + view;
			Vector3 right = view.Cross(up);
			right.y = 0;
			right.Normalize();
			up = right.Cross(view).Normalized();
		}
		if (Application::IsKeyPressed(VK_RIGHT))
		{
			Vector3 view = (target - position).Normalized();
			float yaw = (float)(-CAMERA_SPEED * (float)dt);
			Mtx44 rotation;
			rotation.SetToRotation(yaw, 0, 1, 0);
			view = rotation * view;
			target = position + view;
			Vector3 right = view.Cross(up);
			right.y = 0;
			right.Normalize();
			up = right.Cross(view).Normalized();
		}
		if (Application::IsKeyPressed(VK_UP))
		{
			float pitch = (float)(CAMERA_SPEED * (float)dt);
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
		if (Application::IsKeyPressed(VK_DOWN))
		{
			float pitch = (float)(-CAMERA_SPEED * (float)dt);
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
		//Update the camera direction based on mouse move
		// left-right rotate
		{
			Vector3 view = (target - position).Normalized();
			float yaw = (float)(-CAMERA_SPEED * Application::camera_yaw * (float)dt);
			Mtx44 rotation;
			rotation.SetToRotation(yaw, 0, 1, 0);
			view = rotation * view;
			target = position + view;
			Vector3 right = view.Cross(up);
			right.y = 0;
			right.Normalize();
			up = right.Cross(view).Normalized();
		}
		{
			test_pitch += (float)(-CAMERA_SPEED * Application::camera_pitch * (float)dt);
			if (test_pitch > 60.f) {
				test_pitch = 60.f;
				return;
			}
			if (test_pitch < -60.f) {
				test_pitch = -60.f;
				return;
			}
			float pitch = (float)(-CAMERA_SPEED * Application::camera_pitch * (float)dt);

			Vector3 view = (target - position).Normalized();
			Mtx44 rotation;
			rotation.SetToRotation(pitch, right.x, right.y, right.z);
			view = rotation * view;
			target = position + view;
			Vector3 right = view.Cross(up);
			right.y = 0;
			right.Normalize();
			up = right.Cross(view).Normalized();
		}
		break;
	case THIRDPERSON:

		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);	
		right.Normalize();

		{
			float pitch = -Application::camera_pitch * CAMERA_SPEED * static_cast<float>(dt);
			Vector3 view = (target - position).Normalized();
			Vector3 right = view.Cross(up);
			right.y = 0;
			right.Normalize();
			up = right.Cross(view).Normalized();
			Mtx44 rotation;
			rotation.SetToRotation(pitch, right.x, right.y, right.z);
			position = rotation * position;
			TPSPositionVector = rotation * TPSPositionVector;
		}
		{
			float yaw = -Application::camera_yaw * CAMERA_SPEED * static_cast<float>(dt);
			Mtx44 rotation;
			rotation.SetToRotation(yaw, 0, 1, 0);
			position = rotation * position;
			TPSPositionVector = rotation * TPSPositionVector;
			up = rotation * up;
		}

		position = carPtr->getEntityData()->Translate + TPSPositionVector;

		if (position.y < 1)
			position.y = 1;

		target.Set(carPtr->getEntityData()->Translate.x, carPtr->getEntityData()->Translate.y + 5, carPtr->getEntityData()->Translate.z);
		break;
	}
}


void Camera::Move(float x, float y, float z) {
	Vector3 view = (target - position).Normalized();
	position.x += x;
	position.y += y;
	position.z += z;
	target = position + view;
	
}