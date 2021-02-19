#pragma once
#include "Entity.h"

struct RigidBody {
	Vector3 velocity;
	Vector3 gravity;
	float   airResistanceFactor;
	bool    grounded;

	RigidBody() {
		velocity.SetZero();
		gravity.Set(0, -0.981f, 0);
		airResistanceFactor = 0.035f;
		grounded = false;
	}

	void Update(EntityData* data, double dt) {

		data->Translate = data->Translate + velocity;

		if (data->Translate.y <= 0) data->Translate.y = 0;
		else velocity = velocity + gravity * dt;
		velocity = velocity + (-1 * velocity * airResistanceFactor);

		std::cout << data->Translate.x << " " << data->Translate.y << " " << data->Translate.z << std::endl;
		grounded = false;
	}
};

enum NPCTYPE {
	EGGMAN,
	TAILS,
	TESTNPC,

	NPC_TYPECOUNT
};

class NPC : public Entity
{
	Mesh* associatedNPCMesh;
	const NPCTYPE npcType;
	RigidBody RB;
public:

	NPCTYPE getNPCType();

	NPC(Scene*, NPCTYPE, std::string);
	~NPC();
	RigidBody& getRigidBody();
	void Update(double);
	void Render();
};

