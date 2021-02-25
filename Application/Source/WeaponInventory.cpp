#include "WeaponInventory.h"
#include <iostream>
WeaponInventory::WeaponInventory()
{
	activeWeapon = nullptr;
}

WeaponInventory::WeaponInventory(WEAPON_TYPE wType)
{
	activeWeapon = new Weapon(wType); //add new weapon with corresponding weaponType to argument
	weaponList.push_back(activeWeapon); //push back new weapon into weapon inventory vector
}

WeaponInventory::~WeaponInventory()
{
}

void WeaponInventory::setActiveWeapon(int wType)
{
	for (int i = 0; i < weaponList.size(); i++)
	{
		if (weaponList[i]->getWeaponType() == wType)
		{
			this->activeWeapon = weaponList[i];
			return;
		}
	}
}

//void WeaponInventory::Update(Camera* cam, double dt) {
//	activeWeapon->Update(cam, dt);
//}

void WeaponInventory::addWeapon(WEAPON_TYPE wType)
{
	for (int i = 0; i < weaponList.size(); i++) //check if player owns weapon
		if (weaponList[i]->getWeaponType() == wType) //if yes return and cancel adding of weapon to prevent duplicate
			return;

	//add weapons to vector
	Weapon* temp = new Weapon(wType);
	weaponList.push_back(temp);
	activeWeapon = temp;
}

void WeaponInventory::delWeapon(WEAPON_TYPE wType)
{
	for (int i = 0; i < weaponList.size(); i++)
	{
		if (weaponList[i]->getWeaponType() == wType) //cycle through the vector and find the weapon type to be removed
		{
			delete weaponList[i]; //del weapon
			weaponList[i] = nullptr; //set to nullptr
		}
	}

	weaponList.erase(std::remove(weaponList.begin(), weaponList.end(), nullptr), weaponList.end()); //remove any nullptr from vector

	if (!weaponList.empty()) {
		for (int i = 0; i < weaponList.size(); i++)
		{
			activeWeapon = weaponList[i]; //set nearest slot weapon to active weapon
			return;
		}
	}
	else activeWeapon = nullptr;
}

Weapon* WeaponInventory::getActiveWeapon()
{
	return this->activeWeapon; //return activeWeapon
}

std::vector<Weapon*> WeaponInventory::getWeaponList()
{
	return this->weaponList; //return weaponList vector
}

void WeaponInventory::switchActiveWeapon(int index)
{
	if (this->weaponList.size() > index) {//switch active weapon to index of vector
		if (activeWeapon == weaponList[index])
			activeWeapon = nullptr;
		else
			activeWeapon = weaponList[index];
	}
}

void WeaponInventory::setAmmo(int) {

}

int WeaponInventory::getAmmo()
{
	return 0;
}
