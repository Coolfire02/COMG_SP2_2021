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

	this->hitBox->centerOffset.x = data->Scale.x * this->hitBox->originalCenterOffset.x;
	this->hitBox->centerOffset.y = data->Scale.y * this->hitBox->originalCenterOffset.y;
	this->hitBox->centerOffset.z = data->Scale.z * this->hitBox->originalCenterOffset.z;
	this->hitBox->currentPos = data->Translate;//+ this->hitBox->centerOffset;

	// this->hitBox->xAxis.Set(mtx.a[0], mtx.a[4], mtx.a[8]);
	// this->hitBox->yAxis.Set(mtx.a[1], mtx.a[5], mtx.a[9]);
	// this->hitBox->zAxis.Set(mtx.a[2], mtx.a[6], mtx.a[10]);

	Mtx44 rotation;
	rotation.SetToRotation(data->Rotation.y, 0.f, 1.f, 0.f);
	this->hitBox->xAxis = rotation * this->hitBox->xAxis;
	this->hitBox->yAxis = rotation * this->hitBox->yAxis;
	this->hitBox->zAxis = rotation * this->hitBox->zAxis;

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

