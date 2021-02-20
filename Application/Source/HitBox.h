#pragma once
#include "Vector3.h"
#include "EntityDataHandler.h"
#include "Position3D.h"
#include "Mtx44.h"
#include <vector>

struct Collider {
	bool collided;
	Vector3 translationVector;
	Vector3 normal;
};

struct Box {

	Vector3 originalhalfSize, originalCenterOffset;
	Vector3 currentPos;
	Vector3 xAxis, yAxis, zAxis;
	Vector3 halfSize, centerOffset;
	Mtx44   Rotate;

	static enum selfAxis {
		RIGHT = 1,
		TOP = 2,
		FRONT = 3,
		LEFT = -1,
		BOTTOM = -2,
		BACK = -3,
	};

	selfAxis axisCollided;

	Box(Vector3 botLeftPos, Vector3 topRightPos) {
		Vector3 center = Vector3(botLeftPos.GetMidpoint(botLeftPos, topRightPos));
		this->originalCenterOffset = Vector3(center.x, center.y, center.z);

		this->currentPos = Vector3(center);
		this->originalhalfSize = Vector3(
			(topRightPos.x - botLeftPos.x) / 2.0f,
			(topRightPos.y - botLeftPos.y) / 2.0f,
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

		if (collided) {
			collider.normal = getCollisionPlaneNormal(&otherBox);
			collider.translationVector = getCollisionResponse(&otherBox);
			collider.translationVector.y = 0;
		}

		return collider;
	}

	Vector3 getCollisionPlaneNormal(Box* otherBox) {
		Vector3 RPos;
		RPos = otherBox->currentPos - this->currentPos;
		float lowestOverlap = 0;
		int axisNumber = 0;

		int minmax = 1;

		float offset[4] =
		{
			getOverlap(RPos, otherBox->xAxis, otherBox) * (1.f / (2 * otherBox->halfSize.x)) * (1.f / (2 * halfSize.x)),
			getOverlap(RPos, otherBox->zAxis, otherBox) * (1.f / (2 * otherBox->halfSize.z)) * (1.f / (2 * halfSize.z)),
			getOverlap(RPos, otherBox->xAxis, otherBox) * (1.f / (2 * otherBox->halfSize.x)) * (1.f / (2 * halfSize.x)),
			getOverlap(RPos, otherBox->zAxis, otherBox) * (1.f / (2 * otherBox->halfSize.z)) * (1.f / (2 * halfSize.z)),
		};

		for (int i = 0; i < 4; ++i)
		{
			if (Math::FAbs(offset[i]) > Math::FAbs(lowestOverlap))
			{
				axisNumber = i;
				lowestOverlap = offset[i];
			}
		}

		Vector3 normal;
		Vector3 translationalVector;

		switch (axisNumber)
		{
		case 0:
			normal = otherBox->xAxis;
			break;
		case 1:
			normal = otherBox->zAxis;
			break;
		case 2:
			normal = otherBox->xAxis;
			break;
		case 3:
			normal = otherBox->zAxis;
			break;
		}

		return normal;
	}

	Vector3 getCollisionResponse(Box* otherBox) {
		Vector3 RPos;
		RPos = otherBox->currentPos - this->currentPos;
		float lowestOverlap = 0;
		int axisNumber = 0;

		int minmax = 1;

		float offset[4] =
		{
			getOverlap(RPos, otherBox->xAxis, otherBox) * (1.f / (2 * otherBox->halfSize.x)) * (1.f / (2 * halfSize.x)),
			//getOverlap(RPos, otherBox->yAxis, otherBox) * (1.f / (2 * otherBox->halfSize.y)) * (1.f / (2 * halfSize.y)),
			getOverlap(RPos, otherBox->zAxis, otherBox) * (1.f / (2 * otherBox->halfSize.z)) * (1.f / (2 * halfSize.z)),
			getOverlap(RPos, otherBox->xAxis, otherBox) * (1.f / (2 * otherBox->halfSize.x)) * (1.f / (2 * halfSize.x)),
			//getOverlap(RPos, otherBox->yAxis, otherBox) * (1.f / (2 * otherBox->halfSize.y)) * (1.f / (2 * halfSize.y)),
			getOverlap(RPos, otherBox->zAxis, otherBox) * (1.f / (2 * otherBox->halfSize.z)) * (1.f / (2 * halfSize.z)),
		};

		for (int i = 0; i < 4; ++i)
		{
			if (Math::FAbs(offset[i]) > Math::FAbs(lowestOverlap))
			{
				axisNumber = i;
				lowestOverlap = offset[i];
			}
		}


		Vector3 normal;
		Vector3 translationalVector;

		switch (axisNumber)
		{
		case 0:
			normal = otherBox->xAxis;
			break;
			//case 1:
			//	normal = otherBox->yAxis;
			//	break;
		case 1:
			normal = otherBox->zAxis;
			break;
		case 2:
			normal = otherBox->xAxis;
			break;
			//case 4:
			//	normal = otherBox->yAxis;
			//	break;
		case 3:
			normal = otherBox->zAxis;
			break;
		}

		float magnitude =
			(fabs((xAxis * halfSize.x).Dot(normal)) +
				fabs((yAxis * halfSize.y).Dot(normal)) +
				fabs((zAxis * halfSize.z).Dot(normal)) +
				fabs((otherBox->xAxis * otherBox->halfSize.x).Dot(normal)) +
				fabs((otherBox->yAxis * otherBox->halfSize.y).Dot(normal)) +
				fabs((otherBox->zAxis * otherBox->halfSize.z).Dot(normal))) -
			fabs(RPos.Dot(normal));

		translationalVector = normal * magnitude;

		if (lowestOverlap < 0)
		{
			translationalVector = translationalVector * (-1.f);
		}
		return translationalVector;
	}

	float getOverlap(Vector3& RPos, Vector3 Plane, Box* OtherBox) {
		return RPos.Dot(Plane);
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

