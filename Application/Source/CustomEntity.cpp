#include "CustomEntity.h"


CustomEntity::CustomEntity(Scene* scene, Box* hitBox, std::string name) : Entity(scene, ENTITYTYPE::CUSTOM, name) {
	this->hitBox = new HitBox(hitBox);
}

CustomEntity::~CustomEntity() {
	
}

void CustomEntity::Update(double dt) {

}

void CustomEntity::Render() {
	this->scene->modelStack.PushMatrix();
		this->loadOriginTRS();
	this->scene->modelStack.PopMatrix();

	this->scene->modelStack.PushMatrix();
		this->loadHitBoxTRS();
	this->scene->modelStack.PopMatrix();
}

