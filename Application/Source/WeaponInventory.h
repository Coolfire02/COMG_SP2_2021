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

	std::vector<Weapon*> weaponList; //vector to store player's owned Weapons

	void addWeapon(Weapon* weapon, WEAPON_TYPE wType);
	Weapon* getActiveWeapon();
	void setActiveWeapon(WEAPON_TYPE wType);
};