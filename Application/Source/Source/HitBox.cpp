#include "HitBox.h"

//begin Yong Hong Patch on Yong Hong's HitBox code. 16/2/21
//(HALT)adding: Vector of Boxes, Plane of Interaction, HitBox Slim Patch.
//Trying OBB

//begin Joash Patch on Yong Hong's HitBox code. 18/2/21

/******************************************************************************/
/*!
\file	Hitbox.cpp
\author Tan Yong Hong
\author Joash Foo
\brief
Handles all the collision checks in this class
*/
/******************************************************************************/

/******************************************************************************/
/*!
\brief
Manages all collision checks here. Collision updates will be handled in the scene itself after collision has been checked.
*/
/******************************************************************************/

HitBox::HitBox(Box* box) {
	this->hitBox = box;
}

/******************************************************************************/
/*!
\brief
Returns true if the object's hitbox collides with the other hitbox.
*/
/******************************************************************************/
Collider HitBox::collidedWith(HitBox* other) {
	if (!loaded) return Collider(false);
	return hitBox->isCollidedWith(*other->hitBox);
}

/******************************************************************************/
/*!
\brief
Returns the Box struct of the Hitbox.
*/
/******************************************************************************/
Box* HitBox::getThisTickBox() {
	return hitBox;
}

/******************************************************************************/
/*!
\brief
Updates all values of the hitbox here.
*/
/******************************************************************************/
void HitBox::update(EntityData* data, Mtx44 mtx) {
	UpdatePos(Vector3(mtx.a[12], mtx.a[13], mtx.a[14]));
	UpdateAxis(Vector3(1, 0, 0), Vector3(0, 0, 1));
	RotateAxis(data->Rotation.x, Vector3(1, 0, 0));
	RotateAxis(data->Rotation.y, Vector3(0, 1, 0));
	RotateAxis(data->Rotation.z, Vector3(0, 0, 1));

	this->hitBox->halfSize.x = this->hitBox->originalhalfSize.x * data->Scale.x;
	this->hitBox->halfSize.y = this->hitBox->originalhalfSize.y * data->Scale.y;
	this->hitBox->halfSize.z = this->hitBox->originalhalfSize.z * data->Scale.z;
	if (!loaded) loaded = true;
}

/******************************************************************************/
/*!
\brief
Updates the position of the hitbox.
*/
/******************************************************************************/
void HitBox::UpdatePos(Vector3 pos) {
	this->hitBox->currentPos = pos;
}

/******************************************************************************/
/*!
\brief
Updates the axis of the hitbox and recalculates yAxis, yAxis = zAxis . xAxis.
*/
/******************************************************************************/
void HitBox::UpdateAxis(Vector3 xAxis, Vector3 zAxis) {
	this->hitBox->xAxis = xAxis;
	this->hitBox->zAxis = zAxis;
	this->hitBox->yAxis = zAxis.Cross(xAxis);
}

/******************************************************************************/
/*!
\brief
Rotates the axis of the hitbox
*/
/******************************************************************************/
void HitBox::RotateAxis(float degree, Vector3 rotateAxis) {
	this->hitBox->Rotate.SetToIdentity();
	this->hitBox->Rotate.SetToRotation(degree, rotateAxis.x, rotateAxis.y, rotateAxis.z);
	this->hitBox->xAxis = this->hitBox->Rotate * this->hitBox->xAxis;
	this->hitBox->yAxis = this->hitBox->Rotate * this->hitBox->yAxis;
	this->hitBox->zAxis = this->hitBox->Rotate * this->hitBox->zAxis;
}

HitBox::~HitBox() {
	delete hitBox;
}

