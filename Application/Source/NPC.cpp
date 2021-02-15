#include "NPC.h"


NPC::NPC(Scene* scene, NPCTYPE type, std::string name) : Entity(scene, ENTITYTYPE::LIVE_NPC, name) , npcType(npcType) {
	switch (type) {
	case EGGMAN:
		this->associatedNPCMesh = MeshHandler::getMesh(GEO_SONIC_EGGMAN);
		break;
	case TAILS:
		this->associatedNPCMesh = MeshHandler::getMesh(GEO_SONIC_TAILS);
		break;
	default:
		this->associatedNPCMesh = nullptr;
	}
	this->hitBox = new HitBox(new Box(associatedNPCMesh->botLeftPos, associatedNPCMesh->topRightPos));
}

NPC::~NPC() {

}

NPCTYPE NPC::getNPCType() {
	return npcType;
}

void NPC::Update(double dt) {

}

void NPC::Render() {
	this->scene->modelStack.PushMatrix();
	this->loadOriginTRSIntoStacknHitBox();
	if (this->isVisible()) this->scene->RenderMesh(associatedNPCMesh, this->scene->isLightEnabled());
	this->scene->modelStack.PopMatrix();
}