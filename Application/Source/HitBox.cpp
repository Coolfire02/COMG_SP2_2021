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

void HitBox::update(EntityData* data, Mtx44 mtx) {
<<<<<<< Updated upstream
	this->hitBox->centerOffset.x = this->hitBox->originalCenterOffset.x * data->Scale.x;
	this->hitBox->centerOffset.y = this->hitBox->originalCenterOffset.y * data->Scale.y;
	this->hitBox->centerOffset.z = this->hitBox->originalCenterOffset.z * data->Scale.z;
	this->hitBox->currentPos = data->Translate + this->hitBox->centerOffset;
=======

	this->hitBox->centerOffset.x = data->Scale.x * this->hitBox->originalCenterOffset.x;
	this->hitBox->centerOffset.y = data->Scale.y * this->hitBox->originalCenterOffset.y;
	this->hitBox->centerOffset.z = data->Scale.z * this->hitBox->originalCenterOffset.z;

	//Mtx44 rotation = Mtx44(mtx);
	//Mtx44 rotational;
	//rotational.SetToRotation(data->Rotation.x, 1.f, 0.f, 0.f);
	//rotation = rotation * rotational;
	//rotational.SetToRotation(data->Rotation.y, 0.f, 1.f, 0.f);
	//rotation = rotation * rotational;
	//rotational.SetToRotation(data->Rotation.z, 0.f, 0.f, 1.f);
	//rotation = rotation * rotational;
	//this->hitBox->centerOffset = rotation * this->hitBox->centerOffset;
	
	this->hitBox->currentPos.Set(mtx.a[12], mtx.a[13], mtx.a[14]);
	this->hitBox->currentPos = this->hitBox->currentPos;

>>>>>>> Stashed changes
	this->hitBox->xAxis.Set(mtx.a[0], mtx.a[4], mtx.a[8]);
	this->hitBox->yAxis.Set(mtx.a[1], mtx.a[5], mtx.a[9]);
	this->hitBox->zAxis.Set(mtx.a[2], mtx.a[6], mtx.a[10]);
	this->hitBox->xAxis.Normalize();
	this->hitBox->yAxis.Normalize();
	this->hitBox->zAxis.Normalize();
	
	this->hitBox->halfSize = this->hitBox->originalhalfSize - this->hitBox->originalCenterOffset;
	this->hitBox->halfSize.x *= data->Scale.x;
	this->hitBox->halfSize.y *= data->Scale.y;
	this->hitBox->halfSize.z *= data->Scale.z;
}

HitBox::~HitBox() {
	delete hitBox;
}

