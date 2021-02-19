#pragma once
#include <vector>
#include "Weapon.h"
//Weapon Inventory class created by Jordan on 16/2/2021

class WeaponInventory
{
private:
	Weapon* activeWeapon;
	std::vector<Weapon*> weaponList; //vector to store player's owned Weapons
public:
	WeaponInventory();
	WeaponInventory(WEAPON_TYPE wType);
	~WeaponInventory();

	void addWeapon(Weapon* weapon, WEAPON_TYPE wType);

	Weapon* getActiveWeapon();
	std::vector<Weapon*> getWeaponList();

	void setActiveWeapon(WEAPON_TYPE wType);
};