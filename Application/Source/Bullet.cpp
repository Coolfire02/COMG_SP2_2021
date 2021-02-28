#include "Bullet.h"

Bullet::Bullet() {
}

/******************************************************************************/
/*!
\brief Initialises the Bullet here.

\param type - type of bullet, ENEMYBULLET or PLAYERBULLET
\param velocity - speed of the bullet
\param name - name of the entity
*/
/******************************************************************************/
Bullet::Bullet(Scene* scene, BULLET_TYPE type, Vector3 velocity, std::string name) : Entity(scene, ENTITYTYPE::BULLET, name) {
	this->type = type;
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

/******************************************************************************/
/*!
\brief Gets the velocity of the bullet
\return velocity of the bullet
*/
/******************************************************************************/
Vector3 Bullet::getVelocity() {
	return this->velocity;
}

/******************************************************************************/
/*!
\brief Gets the timer of the bullet to be deleted when passing a certain time limit.
\return the timer of the bullet.
*/
/******************************************************************************/
double Bullet::getTimer()
{
	return timer;
}

void Bullet::Update(double dt) {
}

/******************************************************************************/
/*!
\brief Moves the bullet.
*/
/******************************************************************************/
void Bullet::Move(double dt) {
	this->timer += dt;
	this->data->Translate += velocity * dt;
}

/******************************************************************************/
/*!
\brief Renders the bullet onto the scene's modelStack.
*/
/******************************************************************************/
void Bullet::Render() {
	this->scene->modelStack.PushMatrix();
		this->loadOriginTRSIntoStacknHitBox();
		if (this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(associatedType), this->scene->isLightEnabled());
	this->scene->modelStack.PopMatrix();
}
