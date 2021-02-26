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
	this->up = this->defaultUp = right.Cross(view).Normalized();
	total_pitch = 0;
}



/******************************************************************************/
/*!
\brief
Reset the FirstPersonCamera settings
*/
/******************************************************************************/
void Camera::Reset()
{
	target = position - Vector3(0, 0, 1);
	up = defaultUp;
	total_pitch = 0;
	total_yaw = 0;
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
	if (Application::cursorEnabled) return;
	if (Application::IsKeyPressed('P')) Reset();

	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	static const float CAMERA_SPEED = 100.f;

	yaw = (float)(-CAMERA_SPEED * Application::camera_yaw * (float)dt);
	pitch = (float)(-CAMERA_SPEED * Application::camera_pitch * (float)dt);

	switch (camType) {
	case FIRSTPERSON:
		double x, y;
		Application::GetCursorPos(&x, &y);
		if (yaw != 0)
		{
			total_yaw += (float)(-CAMERA_SPEED * Application::camera_yaw * (float)dt);
			Vector3 view = (target - position).Normalized();
			Mtx44 rotation;
			rotation.SetToRotation(yaw, 0, 1, 0);
			view = rotation * view;
			target = position + view;
			up = rotation * up;
		}
		if (pitch != 0)
		{

			
			total_pitch += (float)(-CAMERA_SPEED * Application::camera_pitch * (float)dt);
			if (total_pitch > 79.f) {
				total_pitch = 79.f;
				return;
			}
			if (total_pitch < -79.f) {
				total_pitch = -79.f;
				return;
			}

			Vector3 view = (target - position).Normalized();
			Vector3 right = view.Cross(up);
			right.Normalize();
			up = right.Cross(view).Normalized();
			Mtx44 rotation;
			rotation.SetToRotation(pitch, right.x, right.y, right.z);
			view = rotation * view;
			target = position + view;
		}

		break;
	case THIRDPERSON:
	{
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();
		{
			Mtx44 rotation;
			rotation.SetToRotation(yaw, 0, 1, 0);
			position = rotation * position;
			TPSPositionVector = rotation * TPSPositionVector;
			up = rotation * up;
		}
		{
			Mtx44 rotation;
			rotation.SetToRotation(pitch, right.x, right.y, right.z);
			position = rotation * position;
			TPSPositionVector = rotation * TPSPositionVector;
		}

		position = playerPtr->getEntityData()->Translate + TPSPositionVector;

		if (position.y < 1)
			position.y = 1;

		target.Set(playerPtr->getEntityData()->Translate.x, playerPtr->getEntityData()->Translate.y + 5, playerPtr->getEntityData()->Translate.z);
		break;
	}
	case TOPDOWN_FIRSTPERSON:
	{
		{
			Vector3 view = (target - position).Normalized();
			total_yaw += (float)(-CAMERA_SPEED * Application::camera_yaw * (float)dt);
			yaw = (float)(-CAMERA_SPEED * Application::camera_yaw * (float)dt);
			Mtx44 rotation;
			rotation.SetToRotation(yaw, 0, 1, 0);
			view = rotation * view;
			target = position + view;
			Vector3 right = view.Cross(up);
			right.y = 0;
			right.Normalize();
			up = right.Cross(view).Normalized();
		}
	}
	break;
	case TOPDOWN_THIRDPERSON:
		break;
	}

}

bool Camera::isLookingAt(Vector3 pos)
{
	float sideA = sqrt(pow(target.x - position.x, 2) + pow(target.y - position.y, 2) + pow(target.z - position.z, 2));
	float sideC = sqrt(pow(pos.x - position.x, 2) + pow(pos.y - position.y, 2) + pow(pos.z - position.z, 2));
	float sideB = sqrt(pow(pos.x - target.x, 2) + pow(pos.y - target.y, 2) + pow(pos.z - target.z, 2));

	float angle = acos((pow(sideA, 2) + pow(sideC, 2) - pow(sideB, 2)) / (2 * sideA * sideC)) * 180 / 3.14159;

	return angle < 10;
}


void Camera::Move(float x, float y, float z) {
	Vector3 view = (target - position).Normalized();
	position.x += x;
	position.y += y;
	position.z += z;
	target = position + view;
	
}