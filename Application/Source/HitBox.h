#pragma once
#include "Vector3.h"
#include "EntityDataHandler.h"
#include "Position3D.h"
#include "Mtx44.h"
#include <vector>

struct Collider {
	bool collided;
	Vector3 plane;
};

struct Box {
	Vector3 originalhalfSize, originalCenterOffset;
	Vector3 currentPos;
	Vector3 xAxis, yAxis, zAxis;
	Vector3 halfSize, centerOffset;
	Mtx44   Rotate;

	Box(Vector3 botLeftPos, Vector3 topRightPos) {
		Vector3 center = Vector3(botLeftPos.GetMidpoint(botLeftPos, topRightPos));
		this->originalCenterOffset = Vector3(center.x, center.y, center.z);

		this->currentPos = Vector3(center);
		this->originalhalfSize = Vector3( 
			(topRightPos.x - botLeftPos.x) / 2.0f ,
			(topRightPos.y - botLeftPos.y) / 2.0f ,
			(botLeftPos.z - topRightPos.z) / 2.0f);
		this->halfSize = Vector3(originalhalfSize);
		this->centerOffset = Vector3(originalCenterOffset);
		this->xAxis.Set(1.0f, 0.f, 0.f);
		this->zAxis.Set(.0f, 0.f, 1.f);
		this->yAxis = zAxis.Cross(xAxis);
		this->Rotate.SetToIdentity();
	}
	
	bool hasSeparatingPlane(Vector3 RPos, Vector3 Plane, Box otherBox) {
		return (fabs(RPos.Dot(Plane)) >
			(
				fabs((this->xAxis * this->halfSize.x).Dot(Plane)) +
				fabs((this->yAxis * this->halfSize.y).Dot(Plane)) +
				fabs((this->zAxis * this->halfSize.z).Dot(Plane)) +
				fabs((otherBox.xAxis * otherBox.halfSize.x).Dot(Plane)) +
				fabs((otherBox.yAxis * otherBox.halfSize.y).Dot(Plane)) +
				fabs((otherBox.zAxis * otherBox.halfSize.z).Dot(Plane))				//Check all the Axes in case the box is rotated
				));
	}

	Collider isCollidedWith(Box otherBox) {
		Vector3 RPos = Vector3(otherBox.currentPos - this->currentPos);
		Collider collider;
		
		bool collided = !(
			hasSeparatingPlane(RPos, this->xAxis, otherBox) ||
			hasSeparatingPlane(RPos, this->yAxis, otherBox) ||
			hasSeparatingPlane(RPos, this->zAxis, otherBox) ||
			hasSeparatingPlane(RPos, otherBox.xAxis, otherBox) ||
			hasSeparatingPlane(RPos, otherBox.yAxis, otherBox) ||
			hasSeparatingPlane(RPos, otherBox.zAxis, otherBox) ||

			hasSeparatingPlane(RPos, this->xAxis.Cross(otherBox.xAxis), otherBox) ||
			hasSeparatingPlane(RPos, this->xAxis.Cross(otherBox.yAxis), otherBox) ||
			hasSeparatingPlane(RPos, this->xAxis.Cross(otherBox.zAxis), otherBox) ||
			hasSeparatingPlane(RPos, this->yAxis.Cross(otherBox.xAxis), otherBox) ||
			hasSeparatingPlane(RPos, this->yAxis.Cross(otherBox.yAxis), otherBox) ||
			hasSeparatingPlane(RPos, this->yAxis.Cross(otherBox.zAxis), otherBox) ||
			hasSeparatingPlane(RPos, this->zAxis.Cross(otherBox.xAxis), otherBox) ||
			hasSeparatingPlane(RPos, this->zAxis.Cross(otherBox.yAxis), otherBox) ||
			hasSeparatingPlane(RPos, this->zAxis.Cross(otherBox.zAxis), otherBox));
		collider.collided = collided;
		return collider;
	}

	~Box() {
	}
};

class HitBox
{
	Box* hitBox;

public:
	HitBox(Box* box);
	~HitBox();

	Box* getThisTickBox();
	void update(EntityData* data, Mtx44 matrix);
	void UpdatePos(Vector3 pos);
	void UpdateAxis(Vector3 xAxis, Vector3 zAxis);
	void RotateAxis(float degree, Vector3 rotateAxis);
	Collider collidedWith(HitBox* other);
};

