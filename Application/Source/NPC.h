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
		grounded = true;
	}

	void Update(EntityData* data, double dt) {
		grounded = false;
		data->Translate = data->Translate + velocity;

		if (data->Translate.y <= 0)
		{
			data->Translate.y = 0;
			grounded = true;
		}
		else velocity = velocity + gravity * dt;

		//clamp NPCs location to within map
		data->Translate.x = Math::Clamp(data->Translate.x, -327.f, 421.f);
		data->Translate.z = Math::Clamp(data->Translate.z, -365.f, 289.f);

		//velocity = velocity + (-1 * velocity * airResistanceFactor);

		//std::cout << data->Translate.x << " " << data->Translate.y << " " << data->Translate.z << std::endl;
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
	int NPCtimer = 0;

public:

	NPCTYPE getNPCType();

	NPC(Scene*, NPCTYPE, std::string);
	~NPC();
	RigidBody& getRigidBody();
	void Update(double);
	void Render();
	void Walk(double);
};

