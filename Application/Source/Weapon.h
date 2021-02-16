#pragma once
#include <vector>

enum WEAPON_TYPE
{
	FIST = 0,
	PISTOL,
	SILENCER,
	WEAPON_COUNT
};

class Weapon
{
private:
	int magazineSize;
	int damage;

public:
	Weapon();
	Weapon(WEAPON_TYPE wType);
	~Weapon();

	static WEAPON_TYPE weaponType;

	void initFist();
	void initPistol();
	void initSilencer();

	void initWeapon(WEAPON_TYPE wType, int ammos, int damages);
};