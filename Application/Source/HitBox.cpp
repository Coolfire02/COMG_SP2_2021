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
	return false;
}

Box* HitBox::getThisTickBox() {
	return hitBox;
}

void HitBox::update(EntityData* data) {
	this->hitBox->currentPos = data->Translate;
	this->hitBox->xAxis.x = 1-data->Rotation.x / 360.f;
	this->hitBox->yAxis.y = 1-data->Rotation.y / 360.f;
	this->hitBox->zAxis.z = 1-data->Rotation.z / 360.f;
	this->hitBox->halfSize.x = this->hitBox->originalhalfSize.x * data->Scale.x;
	this->hitBox->halfSize.y = this->hitBox->originalhalfSize.y * data->Scale.y;
	this->hitBox->halfSize.z = this->hitBox->originalhalfSize.z * data->Scale.z;
}

HitBox::~HitBox() {
	delete hitBox;
}

