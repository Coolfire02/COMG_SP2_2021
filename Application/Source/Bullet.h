#include "Entity.h"
#include "Vector3.h"
#include "MeshHandler.h"

enum BULLET_TYPE {
	ENEMYBULLET,
	PLAYERBULLET
};

/******************************************************************************/
/*!
\file	Bullet.h
\author Joash Foo
\brief
Handles the Bullet Entity in our Game.
*/
/******************************************************************************/

/******************************************************************************/
/*!
		Class Bullet:
\brief Handles the Bullet Entity in our Game.
*/
/******************************************************************************/
class Bullet : public Entity {
	GEOMETRY_TYPE associatedType;
	BULLET_TYPE type;
	Vector3 velocity;

	double timer;
public:
	Bullet();
	Bullet(Scene*, BULLET_TYPE, Vector3, std::string);
	~Bullet();

	Vector3 getVelocity();
	double getTimer();
	void Update(double dt);
	void Move(double dt);
	void Render();
};