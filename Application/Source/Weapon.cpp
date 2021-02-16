#include "Weapon.h"
WEAPON_TYPE Weapon::weaponType;

Weapon::Weapon()
{
	magazineSize = 0;
	damage = 0;
}

Weapon::~Weapon()
{
}

Weapon::Weapon(WEAPON_TYPE wType)
{
	this->weaponType = wType; //set new weaponType
	switch (wType) //based on new weaponType, init the dmg and magSize
	{
	case FIST:
		initFist();
		break;

	case PISTOL:
		initPistol();
		break;

	case SILENCER:
		initSilencer();
		break;

	default:
		initFist();
		break;
	}
}

void Weapon::initFist() //init fist with 0 dmg, 0 magSize
{
	initWeapon(FIST, 0, 0);
}

void Weapon::initPistol() //init fist with 20 dmg, 10 magSize
{
	initWeapon(PISTOL, 20, 10);
}

void Weapon::initSilencer() //init fist with 15 dmg, 15 magSize
{
	initWeapon(SILENCER, 15, 15);
}

void Weapon::initWeapon(WEAPON_TYPE wType, int damages, int magSize) //init weapon with new weaponType, damage and magSize
{
	this->weaponType = wType;
	this->damage = damages;
	this->magazineSize = magSize;
}