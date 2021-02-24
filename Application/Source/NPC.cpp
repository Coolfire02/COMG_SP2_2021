#include "NPC.h"
int NPC::IDcounter = 0;

NPC::NPC(Scene* scene, NPCTYPE type, std::string name) : Entity(scene, ENTITYTYPE::LIVE_NPC, name) , npcType(npcType) {
	switch (type) {
	case TESTNPC:
		this->associatedNPCMesh = MeshHandler::getMesh(GEO_NPC);
		break;
	case DRUGMAN:
		this->associatedNPCMesh = MeshHandler::getMesh(GEO_DRUGMAN);
		break;
	default:
		this->associatedNPCMesh = nullptr;
		break;
	}
	IDcounter++;
	this->ID = IDcounter;
	this->hitBox = new HitBox(new Box(*associatedNPCMesh->botLeftPos, *associatedNPCMesh->topRightPos));
}

NPC::~NPC() {

}

/******************************************************************************/
/*!
\brief
returns the RigidBody of the NPC.
*/
/******************************************************************************/
RigidBody& NPC::getRigidBody()
{
	return this->RB;
}

/******************************************************************************/
/*!
\brief
returns the NPC type.
*/
/******************************************************************************/
NPCTYPE NPC::getNPCType() {
	return npcType;
}

/******************************************************************************/
/*!
\brief
Updates the NPC here.
*/
/******************************************************************************/
void NPC::Update(double dt) {
	RB.Update(this->getEntityData(), dt);
}

/******************************************************************************/
/*!
\brief
Pushes a matrix onto the NPC's scene's modelStack, loads its Transformation matrix and renders the NPC.
*/
/******************************************************************************/
void NPC::Render() {
	this->scene->modelStack.PushMatrix();
		this->loadOriginTRSIntoStacknHitBox();
		if (this->isVisible()) this->scene->RenderMesh(associatedNPCMesh, this->scene->isLightEnabled());
	this->scene->modelStack.PopMatrix();
}

/******************************************************************************/
/*!
\brief
Calculate random angle where the NPC will face and walk towards using frame ticker
*/
/******************************************************************************/
void NPC::Walk(double dt)
{
	NPCtimer += dt;
	if (NPCtimer > 5)
	{
		if (!this->RB.hit) {
			int randomDir = rand() % 360 + 1; //get random direction

			this->getEntityData()->Rotation.Set(0, randomDir, 0); //set NPC rotation to the direction
			this->RB.velocity.Set(0, 0, 1 * dt * 15); //set NPC velocity

			Mtx44 rotation;
			rotation.SetToRotation(randomDir, 0, 1, 0); //make rotation matrix
			this->RB.velocity = rotation * this->RB.velocity; //set the velocity rotation to the direction the NPC is facing
		}
		NPCtimer = 0;
	}
}

int NPC::getID()
{
	return this->ID;
}

std::vector<int>& NPC::getIDList()
{
	return IDList;
}