#include "Car.h"
#include "Application.h"

Car::Car(CAR_TYPE type, Scene* scene, std::string name) : Entity(scene, ENTITYTYPE::CAR, name)
{
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
		this->carSpeed = 1.f;
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
	this->carSpeed = 0.5f;
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

void Car::setPlayer(Player* player) {
	this->plr = player;
}

float Car::getSpeed()
{
	return this->carSpeed;
}

CAR_TYPE Car::getCartype()
{
	return this->carType;
}

Player* Car::getPlayer()
{
	return this->plr;
}

float Car::Interpolate(float GoalVelocity, float CurrentVelocity, double dt) {
	float flDifference = GoalVelocity - CurrentVelocity;

	if (flDifference > dt)
		return CurrentVelocity + dt;

	if (flDifference < -dt)
		return CurrentVelocity - dt;

	return GoalVelocity;
}

void Car::Update(double dt) {

	if (!plr)
		return;

	Mtx44 rotation;
	rotation.SetToRotation(this->getEntityData()->Rotation.y, 0, 1, 0);

	if (Application::IsKeyReleased('W')) {
		this->velocityGoal.x = 0;
		this->velocityGoal.z = 0;
	}

	if (Application::IsKeyPressed('W')) {
		this->velocityGoal = rotation * Vector3(0, 0, 1) * carSpeed;
	}

	if (Application::IsKeyPressed('D') && velocity.Magnitude() > 0) {
		this->getEntityData()->Rotation.y -= dt * 80;
	}

	if (Application::IsKeyPressed('A') && velocity.Magnitude() > 0) {
		this->getEntityData()->Rotation.y += dt * 80;
	}

	if (Application::IsKeyPressed('S')) {
		this->velocityGoal = rotation * Vector3(0, 0, 1) * -carSpeed * 0.25;
	}

	this->velocity.x = Interpolate(velocityGoal.x, this->velocity.x, dt);
	this->velocity.z = Interpolate(velocityGoal.z, this->velocity.z, dt);
	plr->getEntityData()->Translate = this->getEntityData()->Translate;
	this->getEntityData()->Translate += this->velocity;
}

void Car::Render()
{
	this->scene->modelStack.PushMatrix();
	this->loadOriginTRSIntoStacknHitBox();
	if (this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(associatedType), this->scene->isLightEnabled());
	this->scene->modelStack.PopMatrix();
}