#include "NPC.h"


NPC::NPC(Scene* scene, NPCTYPE type, std::string name) : Entity(scene, ENTITYTYPE::LIVE_NPC, name) , npcType(npcType) {
	switch (type) {
	case TESTNPC:
		this->associatedNPCMesh = MeshHandler::getMesh(GEO_SEDAN);
		break;
	default:
		this->associatedNPCMesh = nullptr;
	}
	this->hitBox = new HitBox(new Box(*associatedNPCMesh->botLeftPos, *associatedNPCMesh->topRightPos));
}

NPC::~NPC() {

}

RigidBody& NPC::getRigidBody()
{
	return this->RB;
}

NPCTYPE NPC::getNPCType() {
	return npcType;
}

void NPC::Update(double dt) {
	RB.Update(this->getEntityData(), dt);
}

void NPC::Render() {
	this->scene->modelStack.PushMatrix();
	this->loadOriginTRSIntoStacknHitBox();
	if (this->isVisible()) this->scene->RenderMesh(associatedNPCMesh, this->scene->isLightEnabled());
	this->scene->modelStack.PopMatrix();
}