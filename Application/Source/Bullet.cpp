#include "Bullet.h"

Bullet::Bullet() {
}

Bullet::Bullet(Scene* scene, Vector3 velocity, std::string name) : Entity(scene, ENTITYTYPE::BULLET, name) {
	this->scene = scene;
	this->associatedType = GEO_SPHERE;
	this->velocity = velocity;
	this->timer = 0;

	Mesh* theMesh;
	if (associatedType) {
		theMesh = MeshHandler::getMesh(associatedType);
		this->hitBox = new HitBox(new Box(*theMesh->botLeftPos, *theMesh->topRightPos));
	}
}

Bullet::~Bullet() {
	// do nothing
}

Vector3 Bullet::getVelocity() {
	return this->velocity;
}

double Bullet::getTimer()
{
	return timer;
}

void Bullet::Update(double dt) {
}

void Bullet::Move(double dt) {
	this->timer += dt;
	this->data->Translate += velocity * dt;
}

void Bullet::Render() {
	this->scene->modelStack.PushMatrix();
		this->loadOriginTRSIntoStacknHitBox();
		if (this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(associatedType), this->scene->isLightEnabled());
	this->scene->modelStack.PopMatrix();
}
