#pragma once
// rewrite of entity data by Joash 16/2/21

//struct EntityMeshData {
//	float
//		transX, transY, transZ,
//		rotMag, rotX, rotY, rotZ,
//		scaleX, scaleY, scaleZ;
//	EntityMeshData() : transX(0.f), transY(0.f), transZ(0.f),
//	rotMag(0.f), rotX(0.f), rotY(0.f), rotZ(0.f),
//	scaleX(0.f), scaleY(0.f), scaleZ(0.f) {}
//};

//Level 1, non hierarchical (First item in hierarchical stack will use the data from Entity's EntityData)
//This data is then used to communicate with the HitBox class to update it accordingly
struct EntityData {
	Vector3 Translate;
	Vector3 Rotation;
	Vector3 Scale;

	EntityData() {
		Translate.Set(0, 0, 0);
		Rotation.Set(0, 0, 0);
		Scale.Set(1, 1, 1);
	}

	void setValuesTo(EntityData* other) {
		this->Translate = other->Translate;
		this->Rotation = other->Rotation;
		this->Scale = other->Scale;
	}

	void SetTransform(float x, float y, float z) {
		Translate.x = x;
		Translate.y = y;
		Translate.z = z;
	}

	void SetRotate(float x, float y, float z) {
		Rotation.x = x;
		Rotation.y = y;
		Rotation.z = z;
	}
};
