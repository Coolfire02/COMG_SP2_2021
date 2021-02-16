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

Weapon* WeaponInventory::getActiveWeapon()
{
	return weaponList[activeWeapon->weaponType]; //return activeWeapon
}

void WeaponInventory::setActiveWeapon(WEAPON_TYPE wType)
{
	for (int i = 0; i < weaponList.size(); ++i) //loop through whole vector to see if player owns the weapon
	{
		if (weaponList[i]->weaponType == wType) //if yes then
		{
			activeWeapon = weaponList[i]; //set active weapon
		}
	}		
	return;
}