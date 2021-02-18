#include "Entity.h"
#include <iostream>

Entity::Entity()
{
}

Entity::Entity(Scene* associatedScene, ENTITYTYPE type, std::string name) : scene(associatedScene), type(type), dead(false), name(name), useNewData(true), visible(true) {
	this->data = new EntityData();
	this->oldData = new EntityData();
}

Entity::~Entity() {
	delete data;
	delete oldData;
	delete hitBox;
}

bool Entity::isVisible() {
	return visible;
}

void Entity::setVisibility(bool visible) {
	this->visible = visible;
}

std::string Entity::getName() {
	return name;
}

ENTITYTYPE Entity::getType() {
	return type;
}

void Entity::cancelNextMovement() {
	useNewData = false;
}

void Entity::loadOriginTRS() {
	if (useNewData) {
		this->scene->modelStack.Translate(data->Translate.x, data->Translate.y, data->Translate.z);
		this->scene->modelStack.Rotate(data->Rotation.x, 1.f, 0.f, 0.f);
		this->scene->modelStack.Rotate(data->Rotation.y, 0.f, 1.f, 0.f);
		this->scene->modelStack.Rotate(data->Rotation.z, 0.f, 0.f, 1.f);
		this->scene->modelStack.Scale(data->Scale.x, data->Scale.y, data->Scale.z);
<<<<<<< Updated upstream
		
=======
>>>>>>> Stashed changes
	}
	else {
		this->scene->modelStack.Translate(oldData->Translate.x, oldData->Translate.y, oldData->Translate.z);
		this->scene->modelStack.Rotate(oldData->Rotation.x, 1.f, 0.f, 0.f);
		this->scene->modelStack.Rotate(oldData->Rotation.y, 0.f, 1.f, 0.f);
		this->scene->modelStack.Rotate(oldData->Rotation.z, 0.f, 0.f, 1.f);
<<<<<<< Updated upstream
		this->scene->modelStack.Scale(data->Scale.x, data->Scale.y, data->Scale.z);

	}
}

void Entity::RenderHitbox() {
	this->scene->modelStack.PushMatrix();
	EntityData* data = (useNewData ? this->data : this->oldData);
	
	Vector3 trans = data->Translate;
	trans.x += this->hitBox->getThisTickBox()->centerOffset.x;
	trans.y += this->hitBox->getThisTickBox()->centerOffset.y;
	trans.z += this->hitBox->getThisTickBox()->centerOffset.z;
	
	this->scene->modelStack.Translate(trans.x, trans.y, trans.z);
	this->scene->modelStack.Rotate(data->Rotation.x, 1.f, 0.f, 0.f);
	this->scene->modelStack.Rotate(data->Rotation.y, 0.f, 1.f, 0.f);
	this->scene->modelStack.Rotate(data->Rotation.z, 0.f, 0.f, 1.f);
	this->scene->modelStack.Scale(data->Scale.x, data->Scale.y, data->Scale.z);

	this->hitBox->update(data, this->scene->modelStack.Top());
	
	Mesh* mesh = MeshBuilder::GenerateHitBox("hitbox", *this->getHitBox()->getThisTickBox());
	this->scene->RenderMesh(mesh, false);
	delete mesh;

	this->scene->modelStack.PopMatrix();
}

=======
		this->scene->modelStack.Scale(oldData->Scale.x, oldData->Scale.y, oldData->Scale.z);
	}
}

void Entity::loadHitBoxTRS() {
	EntityData* toUse(useNewData ? data : oldData);
	Vector3 centerOffset = Vector3(this->hitBox->getThisTickBox()->centerOffset);
	this->scene->modelStack.Translate(centerOffset.x, centerOffset.y, centerOffset.z);
	this->scene->modelStack.Translate(toUse->Translate.x, toUse->Translate.y, toUse->Translate.z);
	this->scene->modelStack.Rotate(toUse->Rotation.x, 1.f, 0.f, 0.f);
	this->scene->modelStack.Rotate(toUse->Rotation.y, 0.f, 1.f, 0.f);
	this->scene->modelStack.Rotate(toUse->Rotation.z, 0.f, 0.f, 1.f);
	this->scene->modelStack.Translate(-toUse->Translate.x, -toUse->Translate.y, -toUse->Translate.z);
	this->scene->modelStack.Translate(-centerOffset.x, -centerOffset.y, -centerOffset.z);
	this->currentMtx = Mtx44(this->scene->modelStack.Top());
	this->hitBox->update(data, this->currentMtx);
}
>>>>>>> Stashed changes


const Scene* Entity::getAssociatedScene() {
	return scene;
}

void Entity::setDead(bool dead) {
	this->dead = dead;
}

EntityData* Entity::getEntityData() {
	return data;
}

EntityData* Entity::getOldEntityData() {
	return oldData;
}

bool Entity::usingNewData() {
	return useNewData;
}

HitBox* Entity::getHitBox() {
	return hitBox;
}

void Entity::PreUpdate() {
	if (!useNewData) {
		data->setValuesTo(oldData);
	}

	useNewData = true;
}

void Entity::PostUpdate() {
	oldData->setValuesTo(data);
}

bool Entity::isDead() {
	return dead;
}