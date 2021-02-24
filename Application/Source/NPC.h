#pragma once
#include "Entity.h"

/******************************************************************************/
/*!
\brief
Struct to handle the physics of the NPC. 
Implemented only in NPC as we did not plan to have any physics for other entities.
*/
/******************************************************************************/
struct RigidBody {
	Vector3 velocity;
	Vector3 gravity;
	float   airResistanceFactor; // Factor to determine how fast the NPC slows down in the air.
	bool    grounded; // boolean to check if the NPC is on the ground.
	bool	hit; // boolean to check if the entity has been hit by a car.

	RigidBody() {
		velocity.SetZero();
		gravity.Set(0, -0.981f, 0);
		airResistanceFactor = 0.035f;
		grounded = false;
		hit = false;
	}

	/******************************************************************************/
	/*!
	\brief
	Updates the RigidBody here.
	*/
	/******************************************************************************/
	void Update(EntityData* data, double dt) {
		grounded = false;
		data->Translate = data->Translate + velocity;

		if (data->Translate.y <= 0){
			data->Translate.y = 0;
			grounded = true;
		} else velocity = velocity + gravity * dt;

		//clamp NPCs location to within map
		data->Translate.x = Math::Clamp(data->Translate.x, -327.f, 421.f);
		data->Translate.z = Math::Clamp(data->Translate.z, -365.f, 289.f);

		if (hit) velocity = velocity + (-1 * velocity * airResistanceFactor);
		if (velocity.Magnitude() < 0.02) hit = false;
	}
};

enum NPCTYPE {
	EGGMAN,
	TAILS,
	TESTNPC,

	NPC_TYPECOUNT
};

/******************************************************************************/
/*!
		Class NPC:
\brief NPC class that will involve interactable and non-interactable NPCs.
*/
/******************************************************************************/
class NPC : public Entity
{
	Mesh* associatedNPCMesh; // NPC Mesh
	const NPCTYPE npcType; // NPC type
	RigidBody RB;
	float NPCtimer = 0; // timer for random movement.

public:

	NPCTYPE getNPCType();

	NPC(Scene*, NPCTYPE, std::string);
	~NPC();

	RigidBody& getRigidBody();
	void Update(double);
	void Render();
	void Walk(double);
};

