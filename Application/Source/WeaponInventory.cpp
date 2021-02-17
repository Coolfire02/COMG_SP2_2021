#include "WeaponInventory.h"

WeaponInventory::WeaponInventory()
{
	activeWeapon = nullptr;
}

WeaponInventory::WeaponInventory(Weapon* weapon, WEAPON_TYPE wType)
{
	addWeapon(weapon, wType);
}

WeaponInventory::~WeaponInventory()
{
}

void WeaponInventory::addWeapon(Weapon* weapon, WEAPON_TYPE wType)
{
	weapon = new Weapon(wType); //add new weapon with corresponding weaponType to argument
	weaponList.push_back(weapon); //push back new weapon into weapon inventory vector
	activeWeapon = weapon; //set activeWeapon to new weapon
}

Weapon* WeaponInventory::getActiveWeapon()
{
	return weaponList[activeWeapon->weaponType]; //return activeWeapon
}

std::vector<Weapon*> WeaponInventory::getWeaponList()
{
	return this->weaponList;
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