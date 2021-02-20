#pragma once
#include <vector>

enum WEAPON_TYPE
{
	PISTOL = 0,
	SILENCER,
	WEAPON_COUNT
};

class Weapon
{
private:
	int magazineSize;
	int damage;
	WEAPON_TYPE weaponType;
public:
	Weapon();
	Weapon(WEAPON_TYPE wType);
	~Weapon();

	void initPistol();
	void initSilencer();

	void initWeapon(WEAPON_TYPE wType, int ammos, int damages);

	WEAPON_TYPE getWeaponType();
};