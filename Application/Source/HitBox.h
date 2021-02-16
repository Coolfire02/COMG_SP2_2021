#pragma once
#include "Vector3.h"
#include "EntityDataHandler.h"
#include "Position3D.h"
#include <vector>

struct Box {

	Vector3 currentPos;
	Vector3 xAxis, yAxis, zAxis;
	Vector3 halfSize;

	Box(Position3D botLeftPos, Position3D topRightPos) {
		this->currentPos = Vector3(0, 0, 0);
		this->halfSize = Vector3( 
			(topRightPos.getX() - botLeftPos.getX()) / 2.0f ,
			(topRightPos.getY() - botLeftPos.getY()) / 2.0f ,
			(botLeftPos.getZ() - topRightPos.getZ()) / 2.0f);
		this->xAxis.Set(1.0f, 0.f, 0.f);
		this->yAxis.Set(.0f, 1.f, 0.f);
		this->zAxis.Set(.0f, 0.f, 1.f);
	}

	Box(Vector3 currentPos, Vector3 xAxis, Vector3 yAxis, Vector3 zAxis, Vector3 halfSize) {
		this->currentPos = currentPos;
		this->xAxis = xAxis;
		this->yAxis = yAxis;
		this->zAxis = zAxis;
		this->halfSize = halfSize;
	}

	bool hasSeparatingPlane(Vector3& vector, Vector3 plane, Box& otherBox) {
		return (Math::FAbs(vector.Dot(plane)) > 
			(
			Math::FAbs(plane.Dot(this->xAxis.Dot(this->halfSize.x))) + 
			Math::FAbs(plane.Dot(this->yAxis.Dot(this->halfSize.y))) +
			Math::FAbs(plane.Dot(this->zAxis.Dot(this->halfSize.z))) +
			
			Math::FAbs(plane.Dot(otherBox.xAxis.Dot(otherBox.halfSize.x))) +
			Math::FAbs(plane.Dot(otherBox.yAxis.Dot(otherBox.halfSize.y))) +
			Math::FAbs(plane.Dot(otherBox.zAxis.Dot(otherBox.halfSize.z)))
			));
	}

	bool isCollidedWith(Box& otherBox) {
		static Vector3 vector = otherBox.currentPos - this->currentPos;
		bool collided = !(
			hasSeparatingPlane(vector, this->xAxis, otherBox) ||
			hasSeparatingPlane(vector, this->yAxis, otherBox) ||
			hasSeparatingPlane(vector, this->zAxis, otherBox) ||
			hasSeparatingPlane(vector, otherBox.xAxis, otherBox) ||
			hasSeparatingPlane(vector, otherBox.yAxis, otherBox) ||
			hasSeparatingPlane(vector, otherBox.zAxis, otherBox) ||

			hasSeparatingPlane(vector, this->xAxis.Cross(otherBox.xAxis), otherBox) ||
			hasSeparatingPlane(vector, this->xAxis.Cross(otherBox.yAxis), otherBox) ||
			hasSeparatingPlane(vector, this->xAxis.Cross(otherBox.zAxis), otherBox) ||
			hasSeparatingPlane(vector, this->yAxis.Cross(otherBox.xAxis), otherBox) ||
			hasSeparatingPlane(vector, this->yAxis.Cross(otherBox.yAxis), otherBox) ||
			hasSeparatingPlane(vector, this->yAxis.Cross(otherBox.zAxis), otherBox) ||
			hasSeparatingPlane(vector, this->zAxis.Cross(otherBox.xAxis), otherBox) ||
			hasSeparatingPlane(vector, this->zAxis.Cross(otherBox.yAxis), otherBox) ||
			hasSeparatingPlane(vector, this->zAxis.Cross(otherBox.zAxis), otherBox)
			);
		return collided;
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
	void update(EntityData* data);
	bool collidedWith(HitBox* other);
};

