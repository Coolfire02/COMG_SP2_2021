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

	UpdatePos(Vector3(mtx.a[12], mtx.a[13], mtx.a[14]));
	UpdateAxis(Vector3(1, 0, 0), Vector3(0, 0, 1));
	RotateAxis(data->Rotation.x, Vector3(1, 0, 0));
	RotateAxis(data->Rotation.y, Vector3(0, 1, 0));
	RotateAxis(data->Rotation.z, Vector3(0, 0, 1));

	this->hitBox->halfSize.x = this->hitBox->originalhalfSize.x * data->Scale.x;
	this->hitBox->halfSize.y = this->hitBox->originalhalfSize.y * data->Scale.y;
	this->hitBox->halfSize.z = this->hitBox->originalhalfSize.z * data->Scale.z;
}

void HitBox::UpdatePos(Vector3 pos) {
	this->hitBox->currentPos = pos;
}

void HitBox::UpdateAxis(Vector3 xAxis, Vector3 zAxis) {
	this->hitBox->xAxis = xAxis;
	this->hitBox->zAxis = zAxis;
	this->hitBox->yAxis = zAxis.Cross(xAxis);
}

void HitBox::RotateAxis(float degree, Vector3 rotateAxis) {
	this->hitBox->Rotate.SetToIdentity();
	this->hitBox->Rotate.SetToRotation(degree, rotateAxis.x, rotateAxis.y, rotateAxis.z);
	this->hitBox->xAxis = this->hitBox->Rotate * Vector3(1, 0, 0);
	this->hitBox->yAxis = this->hitBox->Rotate * Vector3(0, 1, 0);
	this->hitBox->zAxis = this->hitBox->Rotate * Vector3(0, 0, 1);
}

HitBox::~HitBox() {
	delete hitBox;
}

