#include "WorldObject.h"

WorldObject::WorldObject(Scene* scene, GEOMETRY_TYPE mesh, std::string str) : Entity(scene, ENTITYTYPE::WORLDOBJ, name), associatedType(mesh) {
	Mesh* theMesh = MeshHandler::getMesh(associatedType);
	this->hitBox = new HitBox(new Box(theMesh->botLeftPos, theMesh->topRightPos));
}

WorldObject::~WorldObject() {}

void WorldObject::Update(double dt) {

}

void WorldObject::Render() {
	this->scene->modelStack.PushMatrix();
		this->loadOriginTRSIntoStacknHitBox();
		if(this->isVisible()) this->scene->RenderMesh(MeshHandler::getMesh(associatedType), this->scene->isLightEnabled());
	this->scene->modelStack.PopMatrix();
}