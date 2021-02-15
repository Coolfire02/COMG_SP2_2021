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
		this->loadOriginTRSIntoStacknHitBox();
	this->scene->modelStack.PopMatrix();
}

