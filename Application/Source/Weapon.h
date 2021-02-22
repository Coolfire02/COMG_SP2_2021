#pragma once
#include <vector>
#include "MeshHandler.h"
// #include "Camera.h"

enum WEAPON_TYPE
{
	PISTOL = 0,
	SILENCER,
	WEAPON_COUNT
};

class Weapon
{
private:
	GEOMETRY_TYPE associatedMeshType;
	WEAPON_TYPE weaponType;

	int magazineSize;
	int damage;

public:
	Weapon();
	Weapon(WEAPON_TYPE wType);
	~Weapon();

	void initPistol();
	void initSilencer();
	void Update(Vector3, double);
	void initWeapon(WEAPON_TYPE wType, int ammos, int damages);

	GEOMETRY_TYPE getMeshType();
	WEAPON_TYPE getWeaponType();
};