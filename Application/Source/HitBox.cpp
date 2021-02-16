#include "HitBox.h"

//begin Yong Hong Patch on Yong Hong's HitBox code. 16/2/21
//(HALT)adding: Vector of Boxes, Plane of Interaction, HitBox Slim Patch.
//Trying OBB

HitBox::HitBox(Box* box) {
	this->hitBox = box;
}

bool HitBox::collidedWith(HitBox* other) {
	if (hitBox->isCollidedWith(*other->hitBox)) {
		return true;
	}
}

void HitBox::update(EntityData* data) {
	this->hitBox->currentPos = data->Translate;
	this->hitBox->xAxis = data->Rotation.x / 360.f;
	this->hitBox->yAxis = data->Rotation.y / 360.f;
	this->hitBox->zAxis = data->Rotation.z / 360.f;
}

HitBox::~HitBox() {
	delete hitBox;
}

