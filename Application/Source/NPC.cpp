#include "NPC.h"


NPC::NPC(Scene* scene, NPCTYPE type, std::string name) : Entity(scene, ENTITYTYPE::LIVE_NPC, name) , npcType(npcType) {
	switch (type) {
	case TESTNPC:
		this->associatedNPCMesh = MeshHandler::getMesh(GEO_NPC);
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

void NPC::Walk(double dt)
{
	NPCtimer += 1;

	switch (NPCtimer % 300) //after 300frames (est 5secs)
	{
	case 0:
		int randomDir = rand() % 360 + 1; //get random direction

		this->getEntityData()->Rotation.Set(0, randomDir, 0); //set NPC rotation to the direction
		this->RB.velocity.Set(0, 0, 1 * dt * 15); //set NPC velocity

		Mtx44 rotation;
		rotation.SetToRotation(randomDir, 0, 1, 0); //make rotation matrix
		this->RB.velocity = rotation * this->RB.velocity; //set the velocity rotation to the direction the NPC is facing
		break;
	}
}