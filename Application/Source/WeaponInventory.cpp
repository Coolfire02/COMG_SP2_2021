#include "WeaponInventory.h"
#include <iostream>

/******************************************************************************/
/*!
\brief
Initialise activeWeapon to nullptr
*/
/******************************************************************************/
WeaponInventory::WeaponInventory()
{
	activeWeapon = nullptr;
	weaponList = std::vector<Weapon*>();
}

/******************************************************************************/
/*!
\brief
Overloaded constructor to create a new weaponInventory with a weapon to start off with
*/
/******************************************************************************/
WeaponInventory::WeaponInventory(WEAPON_TYPE wType)
{
	activeWeapon = new Weapon(wType); //add new weapon with corresponding weaponType to argument
	weaponList.push_back(activeWeapon); //push back new weapon into weapon inventory vector
}

WeaponInventory::~WeaponInventory()
{
}

/******************************************************************************/
/*!
\brief
Sets active weapon based on position of vector
*/
/******************************************************************************/
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

/******************************************************************************/
/*!
\brief
Add weapon function that also pushes back into the weaponList vector
*/
/******************************************************************************/
void WeaponInventory::addWeapon(WEAPON_TYPE wType)
{
	for (int i = 0; i < weaponList.size(); i++) //check if player owns weapon
		if (weaponList[i]->getWeaponType() == wType) //if yes return and cancel adding of weapon to prevent duplicate
			return;

	//add weapon to vector
	Weapon* temp = new Weapon(wType);
	weaponList.push_back(temp);
	activeWeapon = temp;
}

/******************************************************************************/
/*!
\brief
Delete weapon function that removes current equipped weapon (activeWeapon)
*/
/******************************************************************************/
void WeaponInventory::delWeapon(WEAPON_TYPE wType)
{
	for (int i = 0; i < weaponList.size(); i++)
	{
		if (weaponList[i]->getWeaponType() == wType) //cycle through the vector and find the weapon type to be removed
		{
			weaponList.erase(weaponList.begin() + i); //del weapon
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

/******************************************************************************/
/*!
\brief
Return activeWeapon
*/
/******************************************************************************/
Weapon* WeaponInventory::getActiveWeapon()
{
	return this->activeWeapon; //return activeWeapon
}

/******************************************************************************/
/*!
\brief
Return weaponList vector
*/	
/******************************************************************************/
std::vector<Weapon*> WeaponInventory::getWeaponList()
{
	return this->weaponList; //return weaponList vector
}

/******************************************************************************/
/*!
\brief
Function that switches your current activeWeapon
*/
/******************************************************************************/
void WeaponInventory::switchActiveWeapon(int index)
{
	if (this->weaponList.size() > index) { //switch active weapon to index of vector
		if (activeWeapon == nullptr)
			activeWeapon = weaponList[index];
		else
		{
			if (!activeWeapon->Reload)
			{
				if (activeWeapon == weaponList[index])
					activeWeapon = nullptr;
				else
					activeWeapon = weaponList[index];
			}
		}
	}
}

int WeaponInventory::getWeaponDamage()
{
	return activeWeapon->getDamage();
}
