#include "WeaponInventory.h"

WeaponInventory::WeaponInventory()
{
}

WeaponInventory::~WeaponInventory()
{
}

void WeaponInventory::addWeapon(Weapon* weapon, WEAPON_TYPE wType)
{
	weapon = new Weapon(wType); //add new weapon with corresponding weaponType to argument
	weaponList.push_back(weapon); //push back new weapon into weapon inventory vector
	activeWeapon->weaponType = weapon->weaponType; //set activeWeapon to new weapon
}

Weapon* WeaponInventory::getWeapon()
{
	return weaponList[activeWeapon->weaponType]; //return activeWeapon
}