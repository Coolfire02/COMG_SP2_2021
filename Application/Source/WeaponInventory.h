#pragma once
#include <vector>
#include "Weapon.h"

class WeaponInventory
{
private:
	Weapon* activeWeapon;

public:
	WeaponInventory();
	~WeaponInventory();

	std::vector<Weapon*> weaponList;

	void addWeapon(Weapon* weapon, WEAPON_TYPE wType);
	Weapon* getWeapon();
};

