#include "Entity.h"
#include "Vector3.h"
#include "MeshHandler.h"

class Bullet : public Entity {
	GEOMETRY_TYPE associatedType;
	Vector3 velocity;

	double timer;
public:
	Bullet();
	Bullet(Scene*, Vector3, std::string);
	~Bullet();

	Vector3 getVelocity();
	double getTimer();
	void Update(double dt);
	void Move(double dt);
	void Render();
};