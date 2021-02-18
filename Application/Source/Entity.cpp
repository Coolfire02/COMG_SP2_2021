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

void Entity::loadOriginTRSIntoStacknHitBox() {
	EntityData* toUse = (useNewData ? data : oldData);
	this->scene->modelStack.Translate(toUse->Translate.x, toUse->Translate.y, toUse->Translate.z);
	this->scene->modelStack.Rotate(toUse->Rotation.x, 1.f, 0.f, 0.f);
	this->scene->modelStack.Rotate(toUse->Rotation.y, 0.f, 1.f, 0.f);
	this->scene->modelStack.Rotate(toUse->Rotation.z, 0.f, 0.f, 1.f);
	this->scene->modelStack.Scale(toUse->Scale.x, toUse->Scale.y, toUse->Scale.z);
	this->hitBox->update(toUse, this->scene->modelStack.Top());
	this->currentMtx = this->scene->modelStack.Top();
}



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

Mtx44 Entity::getCurrentMtx()
{
	return this->currentMtx;
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