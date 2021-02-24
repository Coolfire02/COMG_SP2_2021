#pragma once
#include <vector>
#include "Weapon.h"
//Weapon Inventory class created by Jordan on 16/2/2021

class WeaponInventory
{
private:
	Weapon* activeWeapon; //weapon ptr to store active weapon
	std::vector<Weapon*> weaponList; //vector to store player's owned Weapons

public:

	WeaponInventory();
	WeaponInventory(WEAPON_TYPE wType);
	~WeaponInventory();
	
	Weapon* getActiveWeapon();
	std::vector<Weapon*> getWeaponList();

	//void Update(Camera*, double);
	void addWeapon(WEAPON_TYPE wType);
	void delWeapon(WEAPON_TYPE wType);
	void switchActiveWeapon(int i);

	void setAmmo(int);
	int getAmmo();
};