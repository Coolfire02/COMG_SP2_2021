#include "Weapon.h"

Weapon::Weapon() //set damage and magSize to 0
{
	damage = 0;
	magazineSize = 0;
}

Weapon::~Weapon()
{
}

Weapon::Weapon(WEAPON_TYPE wType)
{
	switch (wType) //based on new weaponType, init the dmg and magSize
	{
	case PISTOL:
		initPistol();
		break;

	case SILENCER:
		initSilencer();
		break;

	default:
		break;
	}
}

void Weapon::initPistol() //init fist with 20 dmg, 10 magSize
{
	initWeapon(PISTOL, 20, 10);
	associatedMeshType = GEO_PISTOL;
}

void Weapon::initSilencer() //init fist with 15 dmg, 15 magSize
{
	initWeapon(SILENCER, 15, 15);
	associatedMeshType = GEO_PISTOL_S;
}

void Weapon::initWeapon(WEAPON_TYPE wType, int damages, int magSize) //init weapon with new weaponType, damage and magSize
{
	this->weaponType = wType;
	this->damage = damages;
	this->magazineSize = magSize;
}

GEOMETRY_TYPE Weapon::getMeshType()
{
	return associatedMeshType;
}

WEAPON_TYPE Weapon::getWeaponType()
{
	if (this != nullptr)
		return this->weaponType;
}
