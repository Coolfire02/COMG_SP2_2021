#include "Car.h"
#include "Application.h"
/******************************************************************************/
/*!
\brief
Calls the Init() function to initialise the car
*/
/******************************************************************************/
Car::Car(CAR_TYPE type, Scene* scene, std::string name) : Entity(scene, ENTITYTYPE::CAR, name)
{
	this->Init(type, scene, name);
}

Car::~Car()
{
}

/******************************************************************************/
/*!
\brief
Initialise all parameters of the car here. e.g. carSpeed, carType, etc.
*/
/******************************************************************************/
void Car::Init(CAR_TYPE type, Scene* scene, std::string name) {

	this->maxCarSpeed = 0.5f;
	this->carSpeed = 0.f;
	this->drifting = false;
	this->carType = type;
	this->scene = scene;
	this->name = name;

	Mesh* theMesh;

	switch (carType) {
	case SEDAN:
		this->maxCarSpeed = 0.5f;
		this->associatedType = GEO_SEDAN;
		break;
	case SEDAN_SPORTS:
		this->maxCarSpeed = 0.75f;
		this->associatedType = GEO_SEDAN_SPORTS;
		break;
	case RACER:
		this->maxCarSpeed = 1.5f;
		this->associatedType = GEO_RACER;
		break;
	case POLICE:
		this->maxCarSpeed = 0.5f;
		this->associatedType = GEO_POLICE;
		break;
	case AMBULANCE:
		this->maxCarSpeed = 0.5f;
		this->associatedType = GEO_AMBULANCE;
		break;
	case SUV:
		this->maxCarSpeed = 0.5f;
		this->associatedType = GEO_SUV;
		break;
	default:
		break;
	}

	if (associatedType) {
		theMesh = MeshHandler::getMesh(associatedType);
		this->hitBox = new HitBox(new Box(*theMesh->botLeftPos, *theMesh->topRightPos));
	}

}

Car::Car()
{
}

/******************************************************************************/
/*!
\brief
Sets the car's speed to a float value.
*/
/******************************************************************************/
void Car::setSpeed(float speed)
{
	driftVector = -velocity * 0.2f;
	this->carSpeed = speed;
}

/******************************************************************************/
/*!
\brief
Sets the car's acceleration to a float value.
*/
/******************************************************************************/
void Car::setAccel(float a) {
	acceleration = a;
}

/******************************************************************************/
/*!
\brief
Sets the player pointer in Car to the player.
*/
/******************************************************************************/
void Car::setPlayer(Player* player) {
	this->plr = player;
}

/******************************************************************************/
/*!
\brief
returns the acceleration value.
*/
/******************************************************************************/
float Car::getAccel() {
	return acceleration;
}

/******************************************************************************/
/*!
\brief
returns the car's speed value.
*/
/******************************************************************************/
float Car::getSpeed()
{
	return this->carSpeed;
}

/******************************************************************************/
/*!
\brief
Sets the velocity vector.
*/
/******************************************************************************/
void Car::setVelocity(Vector3 velocity)
{
	this->velocity = velocity;
}

/******************************************************************************/
/*!
\brief
returns the velocity vector.
*/
/******************************************************************************/
Vector3 Car::getVelocity() {
	return this->velocity;
}

float Car::getMaxCarSpeed(CAR_TYPE carType)
{
	switch (carType) {
	case SEDAN:
		return 0.5f;
		break;
	case SEDAN_SPORTS:
		return 0.75f;
		break;
	case RACER:
		return 1.5f;
		break;
	case POLICE:
		return 0.5f;
		break;
	case AMBULANCE:
		return 0.5f;
		break;
	case SUV:
		return 0.5f;
		break;
	default:
		return 0.f;
		break;
	}
}

/******************************************************************************/
/*!
\brief
returns the car's enum type.
*/
/******************************************************************************/
CAR_TYPE Car::getCartype()
{
	return this->carType;
}

/******************************************************************************/
/*!
\brief
returns the player pointer.
*/
/******************************************************************************/
Player* Car::getPlayer()
{
	return this->plr;
}

/******************************************************************************/
/*!
\brief
Updates the car's position.
velocity = acceleration / time
*/
/******************************************************************************/
void Car::Drive(double dt) {

	acceleration = 0;
	float RotateSpeed = 80.f;
	float friction = carSpeed * -0.5;
	carSpeed += friction * dt * 2.f;

	//Car Boosting by Jordan
	if (!boosting) //refill boostMeter when not boosting
		boostMeter += dt;

	if (boostMeter > 2) //max cap boostMeter to 2 seconds
		boostMeter = 2;

	boosting = false; //default boosting to false when driving
	float boostMaxCarSpeed = maxCarSpeed * 3.f; //3x boost multiplier
	if (boostMaxCarSpeed > 2) //max cap boostMaxCarSpeed to 2.
		boostMaxCarSpeed = 2;

	if (plr) {
		// Set the drift vector to the velocity when started drifting
		if (Application::IsKeyReleased(VK_LSHIFT) && drifting) {
			RotateSpeed = 80.f;
			drifting = false;
			carSpeed = 0;
			velocity = driftVector.Magnitude() * velocity * 2.f;
			// velocity = carSpeed * velocity.Normalized() * dt;
		}

		if (Application::IsKeyPressed('W'))
		{
			acceleration = maxCarSpeed;
			if (boosting) //if boosting, acceleration will be overwritten to boostMaxCarSpeed
				acceleration = boostMaxCarSpeed;
		}


		// set the drift vector to the velocity at the start of the drift
		if (Application::IsKeyPressed(VK_LSHIFT) && !drifting && velocity.Magnitude() > 0.8 && (Application::IsKeyPressed('D') || Application::IsKeyPressed('A'))) {
			RotateSpeed = 100.f;
			drifting = true;
			driftVector = Vector3(velocity);
		}

		// the car's velocity is based on rotation of the car
		if (Application::IsKeyPressed('D')) {
			if (carSpeed > 0.05) this->getEntityData()->Rotation.y -= dt * RotateSpeed;
			if (carSpeed < -0.05) this->getEntityData()->Rotation.y += dt * RotateSpeed;
		}

		if (Application::IsKeyPressed('A')) {
			if ((carSpeed > 0.05)) this->getEntityData()->Rotation.y += dt * RotateSpeed;
			if ((carSpeed < -0.05)) this->getEntityData()->Rotation.y -= dt * RotateSpeed;
		}

		// reverse is slower than forward movement
		if (Application::IsKeyPressed('S')) {
			acceleration = -maxCarSpeed * 0.5f;
		}

		if (Application::IsKeyPressed(VK_SPACE) && (Application::IsKeyPressed('W')))
		{
			if (boostMeter > 0)
			{
				boosting = true; //set boosting to true when "SPACE" is pressed/held
				carSpeed = carSpeed * 1.015; //boost current car speed
				boostMeter -= dt;
			}
		}
		plr->getEntityData()->Translate = this->getEntityData()->Translate;
	}

	if (this->getEntityData()->Rotation.y >= 360 || this->getEntityData()->Rotation.y <= -360)
		this->getEntityData()->Rotation.y = 0;

	Mtx44 rotation;
	rotation.SetToRotation(this->getEntityData()->Rotation.y, 0, 1, 0);

	if (carSpeed < maxCarSpeed && carSpeed > -maxCarSpeed * 0.75f)
		carSpeed = carSpeed + acceleration * dt;

	if (boosting) //if boosting, maxCarSpeed will be overwritten to boostMaxCarSpeed
	{
		if (carSpeed < boostMaxCarSpeed && carSpeed > -boostMaxCarSpeed * 0.75f)
			carSpeed = carSpeed + acceleration * dt;
	}

	this->velocity = rotation * Vector3(0, 0, 1) * carSpeed;
	this->driftVector = (driftVector - driftVector * dt);


	// v = at
	if (drifting) {
		this->getEntityData()->Translate = this->getEntityData()->Translate + driftVector + velocity * dt;
	}
	else this->getEntityData()->Translate = this->getEntityData()->Translate + this->velocity + driftVector;
}

float Car::getBoostMeter()
{
	return boostMeter;
}

void Car::Update(double dt) {
}

/******************************************************************************/
/*!
\brief
Pushes a matrix onto the car's scene's modelStack, loads its Transformation matrix and renders the car.
*/
/******************************************************************************/
void Car::Render()
{
	this->scene->modelStack.PushMatrix();
	this->loadOriginTRSIntoStacknHitBox();
	if (this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(associatedType), this->scene->isLightEnabled());
	this->scene->modelStack.PopMatrix();
}