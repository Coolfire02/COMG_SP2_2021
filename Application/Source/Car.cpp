#include "Car.h"
#include "Application.h"

Car::Car(CAR_TYPE type, Scene* scene, std::string name) : Entity(scene, ENTITYTYPE::CAR, name)
{
	this->maxCarSpeed = 0.5f;
	this->carSpeedGoal = this->carSpeed = 0.f;
	this->driftFalloff = 0.f;
	this->carType = type;
	this->scene = scene;
	this->name = name;
	this->drifting = false;
	this->Init();
}

Car::~Car()
{
}

void Car::Init() {

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

	if (associatedType != 0) {
		theMesh = MeshHandler::getMesh(associatedType);
		this->hitBox = new HitBox(new Box(*theMesh->botLeftPos, *theMesh->topRightPos));
	}

}

Car::Car()
{
}

Car::Car(float speed, CAR_TYPE type)
{
	this->carSpeed = speed;
	this->carType = type;
}

void Car::setSpeed(float speed)
{
	this->carSpeed = speed;
}

void Car::setAccel(float a) {
	acceleration = a;
}

void Car::setPlayer(Player* player) {
	this->plr = player;
}

float Car::getAccel() {
	return acceleration;
}

float Car::getSpeed()
{
	return this->carSpeed;
}

Vector3 Car::getVelocity() {
	return this->velocity;
}

CAR_TYPE Car::getCartype()
{
	return this->carType;
}

Player* Car::getPlayer()
{
	return this->plr;
}

void Car::Drive(double dt) {
	if (!plr)
		return;

	acceleration = 0;
	float RotateSpeed = 80.f;
	float friction = carSpeed * -0.5;
	carSpeed += friction * dt * 2.f;

	if (Application::IsKeyReleased(VK_LSHIFT) && drifting) { 
		RotateSpeed = 80.f;
		drifting = false; 
		carSpeed = 0;
		velocity = driftVector.Magnitude() * velocity.Normalized();
		// velocity = carSpeed * velocity.Normalized() * dt;
	}
	
	if (Application::IsKeyPressed('W')) acceleration = maxCarSpeed;

	if (Application::IsKeyPressed(VK_LSHIFT) && !drifting && velocity.Magnitude() > 0.6 && (Application::IsKeyPressed('D') || Application::IsKeyPressed('A'))) {
		RotateSpeed = 100.f;
		drifting = true;
		driftVector = Vector3(velocity);
	}

	if (Application::IsKeyPressed('D')) {
		if (carSpeed > 0.05) this->getEntityData()->Rotation.y -= dt * RotateSpeed;
		if (carSpeed < -0.05) this->getEntityData()->Rotation.y += dt * RotateSpeed;
	}

	if (Application::IsKeyPressed('A')) {
		if ((carSpeed > 0.05)) this->getEntityData()->Rotation.y += dt * RotateSpeed;
		if ((carSpeed < -0.05)) this->getEntityData()->Rotation.y -= dt * RotateSpeed;
	}

	if (Application::IsKeyPressed('S')) {
		acceleration = -maxCarSpeed * 0.5f;
		// this->velocity = rotation * Vector3(0, 0, 1) * -carSpeed * 0.25;
	}

	// this->velocity.x = Interpolate(velocityGoal.x, this->velocity.x, dt);
	// this->velocity.z = Interpolate(velocityGoal.z, this->velocity.z, dt);
	if (this->getEntityData()->Rotation.y >= 360 || this->getEntityData()->Rotation.y <= -360)
		this->getEntityData()->Rotation.y = 0;

	Mtx44 rotation;
	rotation.SetToRotation(this->getEntityData()->Rotation.y, 0, 1, 0);

	// carSpeed = Interpolate(carSpeedGoal, carSpeed, dt);
	if (carSpeed < maxCarSpeed && carSpeed > -maxCarSpeed * 0.75f)
		carSpeed = carSpeed + acceleration * dt;

	std::cout << velocity.Magnitude() << std::endl;

	this->velocity = rotation * Vector3(0, 0, 1) * carSpeed;
	this->driftVector = driftVector - driftVector * dt;
	plr->getEntityData()->Translate = this->getEntityData()->Translate;
	if (drifting) {
		this->getEntityData()->Translate = this->getEntityData()->Translate + driftVector + velocity * dt;
	}
	else
		this->getEntityData()->Translate = this->getEntityData()->Translate + this->velocity + driftVector;

}

void Car::Update(double dt) {
}

void Car::Render()
{
	this->scene->modelStack.PushMatrix();
	this->loadOriginTRSIntoStacknHitBox();
	if (this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(associatedType), this->scene->isLightEnabled());
	this->scene->modelStack.PopMatrix();
}