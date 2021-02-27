#include "NPC.h"
int NPC::IDcounter = 0;

/******************************************************************************/
/*!
\brief
Overloaded constructor that sets variables based on parameters
*/
/******************************************************************************/
NPC::NPC(Scene* scene, NPCTYPE type, std::string name, int health) : Entity(scene, ENTITYTYPE::LIVE_NPC, name, health) , npcType(npcType) {
	switch (type) {
	case TESTNPC:
		this->associatedNPCMesh = MeshHandler::getMesh(GEO_NPC);
		break;
	case DRUGMAN:
		this->associatedNPCMesh = MeshHandler::getMesh(GEO_DRUGMAN);
		break;
	case BIMSTER:
		this->associatedNPCMesh = MeshHandler::getMesh(GEO_BIMSTER);
		break;
	default:
		this->associatedNPCMesh = nullptr;
		break;
	}
	semiCollision = true;
	IDcounter++;
	this->ID = IDcounter;
	this->maxHealth = health;
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
Returns whether this NPC should interact with most things
*/
/******************************************************************************/
bool NPC::getSemiCollision() {
	return semiCollision;
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
	int maxScale = this->getHealth() * 0.05; //get max scale of healthbar
	if (maxScale > 5) //if maxscale of health bar is too high
		maxScale = 5; //set to max

	if (this->getHealth() < this->maxHealth) //spawn healthbar on top of NPC if health is lesser than max health
	{
		this->scene->modelStack.PushMatrix();
		this->scene->modelStack.Translate(getEntityData()->Translate.x, getEntityData()->Translate.y + 3, getEntityData()->Translate.z);
		this->scene->modelStack.Rotate(this->getEntityData()->Rotation.y, 0, 1, 0);
		this->scene->modelStack.Scale(maxScale, 0.3, 0.01);
		this->scene->RenderMesh(MeshHandler::getMesh(GEO_HEALTHBAR), false);
		this->scene->modelStack.PopMatrix();
	}

	this->scene->modelStack.PushMatrix();
		this->loadOriginTRSIntoStacknHitBox();
		if (this->isVisible()) this->scene->RenderMesh(associatedNPCMesh, this->scene->isLightEnabled());
	this->scene->modelStack.PopMatrix();
}

/******************************************************************************/
/*!
\brief
Calculate random angle where the NPC will face and walk towards using a timer
*/
/******************************************************************************/
void NPC::Walk(double dt)
{
	NPCtimer += dt;
	if (NPCtimer > 10)
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

/******************************************************************************/
/*!
\brief
Returns NPC's ID
*/
/******************************************************************************/
int NPC::getID()
{
	return this->ID;
}

/******************************************************************************/
/*!
\brief
Returns NPC IDList
*/
/******************************************************************************/
std::vector<int>& NPC::getIDList()
{
	return IDList;
}