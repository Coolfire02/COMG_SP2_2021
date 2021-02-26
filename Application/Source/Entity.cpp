#include "Entity.h"
#include <iostream>

Entity::Entity()
{
}

Entity::Entity(Scene* associatedScene, ENTITYTYPE type, std::string name) : scene(associatedScene), type(type), dead(false), name(name), useNewData(true), visible(true) {
	this->data = new EntityData();
	this->oldData = new EntityData();
	this->health = 0;
}

Entity::Entity(Scene* associatedScene, ENTITYTYPE type, std::string name, int health) : scene(associatedScene), type(type), dead(false), name(name), useNewData(true), visible(true) {
	this->data = new EntityData();
	this->oldData = new EntityData();
	this->health = health;
}

Entity::Entity(Scene* associatedScene, ENTITYTYPE type, std::string name, Vector3 pos) : scene(associatedScene), type(type), dead(false), name(name), useNewData(true), visible(true) {
	this->data = new EntityData();
	this->oldData = new EntityData();
	this->data->Translate = pos;
	this->oldData->Translate = pos;
	this->health = 50;
}

Entity::~Entity() {
	delete data;
	delete oldData;
	delete hitBox;
}


void Entity::setType(ENTITYTYPE type) {
	this->type = type;
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

	this->scene->modelStack.PushMatrix();
		this->scene->modelStack.Translate(this->hitBox->getThisTickBox()->originalCenterOffset.x, this->hitBox->getThisTickBox()->originalCenterOffset.y, this->hitBox->getThisTickBox()->originalCenterOffset.z);
		this->currentMtx = this->scene->modelStack.Top();
	this->scene->modelStack.PopMatrix();

	this->hitBox->update(toUse, currentMtx);
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

int Entity::getHealth()
{
	return this->health;
}

void Entity::setHealth(int h)
{
	this->health = h;
}

bool Entity::isDead() {
	return dead;
}