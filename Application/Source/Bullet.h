#include "Entity.h"
#include "Vector3.h"
#include "MeshHandler.h"

enum BULLET_TYPE {
	ENEMYBULLET,
	PLAYERBULLET
};

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