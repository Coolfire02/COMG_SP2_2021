#include "HitBox.h"

//begin Yong Hong Patch on Yong Hong's HitBox code. 16/2/21
//(HALT)adding: Vector of Boxes, Plane of Interaction, HitBox Slim Patch.
//Trying OBB

HitBox::HitBox(Box* box) {
	this->hitBox = box;
}

Collider HitBox::collidedWith(HitBox* other) {
	return hitBox->isCollidedWith(*other->hitBox);
}

Box* HitBox::getThisTickBox() {
	return hitBox;
}

void HitBox::update(EntityData* data, Mtx44 mtx) {
	Vector3 newCenterOffset;
	newCenterOffset = this->hitBox->originalCenterOffset;
	newCenterOffset.x *= data->Scale.x;
	newCenterOffset.y *= data->Scale.y;
	newCenterOffset.z *= data->Scale.z;

	this->hitBox->currentPos = data->Translate +  newCenterOffset;
	this->hitBox->xAxis.Set(mtx.a[0], mtx.a[4], mtx.a[8]);
	this->hitBox->yAxis.Set(mtx.a[1], mtx.a[5], mtx.a[9]);
	this->hitBox->zAxis.Set(mtx.a[2], mtx.a[6], mtx.a[10]);
	this->hitBox->xAxis.Normalize();
	this->hitBox->yAxis.Normalize();
	this->hitBox->zAxis.Normalize();
	this->hitBox->halfSize.x = this->hitBox->originalhalfSize.x * data->Scale.x;
	this->hitBox->halfSize.y = this->hitBox->originalhalfSize.y * data->Scale.y;
	this->hitBox->halfSize.z = this->hitBox->originalhalfSize.z * data->Scale.z;
	
}

HitBox::~HitBox() {
	delete hitBox;
}

