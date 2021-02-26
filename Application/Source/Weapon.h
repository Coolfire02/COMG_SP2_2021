#pragma once
#include <vector>
#include "MeshHandler.h"
#include "Scene.h"
#include "Bullet.h"
#include "EntityManager.h"
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

	int currentAmmo;
	int magazineSize;
	int damage;
	bool shoot = false;

	float reloadTillTime = 0;

	double UIcooldown = 0;

public:
	bool Reload = false;

	Weapon();
	Weapon(WEAPON_TYPE wType);
	~Weapon();

	void initPistol();
	void initSilencer();
	void Update(Scene*, EntityManager*, Vector3, Vector3, double);
	void initWeapon(WEAPON_TYPE wType, int ammos, int damages);

	GEOMETRY_TYPE getMeshType();
	WEAPON_TYPE getWeaponType();
	int getWeaponAmmo();

	void setUIcooldown(double);
	double getUIcooldown();

	int getDamage();
};