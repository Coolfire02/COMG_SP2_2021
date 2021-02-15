#include "Entity.h"
#include <iostream>

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
	if (useNewData) {
		this->scene->modelStack.Translate(data->transX, data->transY, data->transZ);
		this->scene->modelStack.Rotate(data->rotXMag, 1.f, 0.f, 0.f);
		this->scene->modelStack.Rotate(data->rotYMag, 0.f, 1.f, 0.f);
		this->scene->modelStack.Rotate(data->rotZMag, 0.f, 0.f, 1.f);
		this->scene->modelStack.Scale(data->scaleX, data->scaleY, data->scaleZ);
		this->hitBox->update(this->scene->modelStack.Top());
	}
	else {
		this->scene->modelStack.Translate(oldData->transX, oldData->transY, oldData->transZ);
		this->scene->modelStack.Rotate(oldData->rotXMag, 1.f, 0.f, 0.f);
		this->scene->modelStack.Rotate(oldData->rotYMag, 0.f, 1.f, 0.f);
		this->scene->modelStack.Rotate(oldData->rotZMag, 0.f, 0.f, 1.f);
		this->scene->modelStack.Scale(oldData->scaleX, oldData->scaleY, oldData->scaleZ);
		this->hitBox->update(this->scene->modelStack.Top());
	}
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