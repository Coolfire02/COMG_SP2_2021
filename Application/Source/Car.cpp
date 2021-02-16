#include "Car.h"

Car::Car(CAR_TYPE type, Scene* scene, std::string name) : Entity(scene, ENTITYTYPE::CAR, name)
{
	this->seated = false;
	this->carType = type;
	this->scene = scene;
	this->name = name;
	this->Init();
}

Car::~Car()
{
}

void Car::Init() {

	Mesh* theMesh;
	
	switch (carType) {
	case SEDAN:
		this->associatedType = GEO_SEDAN;
		theMesh = MeshHandler::getMesh(associatedType);
		this->hitBox = new HitBox(new Box(theMesh->botLeftPos, theMesh->topRightPos));
		break;
	case SEDAN_SPORTS:
		this->associatedType = GEO_SEDAN_SPORTS;
		theMesh = MeshHandler::getMesh(associatedType);
		this->hitBox = new HitBox(new Box(theMesh->botLeftPos, theMesh->topRightPos));
		break;
	case RACER:
		this->associatedType = GEO_RACER;
		theMesh = MeshHandler::getMesh(associatedType);
		this->hitBox = new HitBox(new Box(theMesh->botLeftPos, theMesh->topRightPos));
		break;
	case POLICE:
		this->associatedType = GEO_POLICE;
		theMesh = MeshHandler::getMesh(associatedType);
		this->hitBox = new HitBox(new Box(theMesh->botLeftPos, theMesh->topRightPos));
		break;
	case AMBULANCE:
		this->associatedType = GEO_AMBULANCE;
		theMesh = MeshHandler::getMesh(associatedType);
		this->hitBox = new HitBox(new Box(theMesh->botLeftPos, theMesh->topRightPos));
		break;
	case SUV:
		this->associatedType = GEO_SUV;
		theMesh = MeshHandler::getMesh(associatedType);
		this->hitBox = new HitBox(new Box(theMesh->botLeftPos, theMesh->topRightPos));
		break;
	default:
		break;
	}
	this->carSpeed = 1.f;
}

void Car::setSpeed(float speed)
{
	this->carSpeed = speed;
}
float Car::getSpeed()
{
	return this->carSpeed;
}

CAR_TYPE Car::getCartype()
{
	return this->carType;
}

float Interpolate(float GoalVelocity, float CurrentVelocity, double dt) {
	float flDifference = GoalVelocity - CurrentVelocity;

	if (flDifference > dt)
		return CurrentVelocity + dt;

	if (flDifference < -dt)
		return CurrentVelocity - dt;

	return GoalVelocity;
}

void Car::Update(double) {
	if (this->seated);

}

void Car::Render()
{
	this->scene->modelStack.PushMatrix();
		this->loadOriginTRSIntoStacknHitBox();
		if (this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(associatedType), this->scene->isLightEnabled());
	this->scene->modelStack.PopMatrix();
}
