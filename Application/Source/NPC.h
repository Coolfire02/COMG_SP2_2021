#pragma once
#include "Entity.h"

enum NPCTYPE {
	EGGMAN,
	TAILS,

	NPC_TYPECOUNT
};

class NPC : public Entity
{
	Mesh* associatedNPCMesh;
	const NPCTYPE npcType;
public:

	NPCTYPE getNPCType();

	NPC(Scene*, NPCTYPE, std::string);
	~NPC();
	void Update(double);
	void Render();
};

