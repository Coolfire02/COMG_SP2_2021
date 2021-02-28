#include "Weapon.h"
#include "Application.h"
#include "Debug.h"
#include "Vector3.h"
#include "AudioHandler.h"
/******************************************************************************/
/*!
\brief
Calls the Init() function to initialise weapons
*/
/******************************************************************************/
Weapon::Weapon() //set damage and magSize to 0
{
	damage = 0;
	magazineSize = 0;
	currentAmmo = 0;
}

Weapon::~Weapon()
{
}
/******************************************************************************/
/*!
\brief
Initialise weaponType based on parameter
*/
/******************************************************************************/
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

	case FIRE_EXTINGUISHER:
		initExtinguisher();
		break;

	default:
		break;
	}
}

void Weapon::initExtinguisher() {
	initWeapon(FIRE_EXTINGUISHER, 10, 1);
	associatedMeshType = GEO_FIREEXTINGUISHER;
}

/******************************************************************************/
/*!
\brief
Initialise pistol with 20 dmg, 10 magSize
*/
/******************************************************************************/
void Weapon::initPistol()
{
	initWeapon(PISTOL, 20, 10);
	associatedMeshType = GEO_PISTOL;
}

/******************************************************************************/
/*!
\brief
Initialise pistol with 15 dmg, 15 magSize
*/
/******************************************************************************/
void Weapon::initSilencer() //init silencer with 15 dmg, 15 magSize
{
	initWeapon(SILENCER, 15, 15);
	associatedMeshType = GEO_PISTOL_S;
}

/******************************************************************************/
/*!
\brief
Updates weapon (shooting, reloading, audio, etc)
*/
/******************************************************************************/
void Weapon::Update(Scene* scene, EntityManager* eManager, Vector3 plrPos, Vector3 view, double dt) {
	if (this != nullptr)
	{
		this->UIcooldown -= dt;
		if (Game::uiManager.getCurrentMenu() == UI_GENERAL) {
			if (this->weaponType == FIRE_EXTINGUISHER && Application::IsMousePressed(0) && !shoot) {
				shoot = true;
				ISound* extinguishSound = AudioHandler::getEngine()->play3D(
					AudioHandler::getSoundSource(SOUNDTYPE::FIRE_EXTINGUISH),
					AudioHandler::to_vec3df(Vector3(0, 0, 0)),
					LOOPED::NOLOOP,
					false,
					true);

				extinguishSound->setVolume(0.3);
			}

			else if (Application::IsMousePressed(0) && !shoot && !Reload && this->currentAmmo >= 0 && UIcooldown < 0) {
				shoot = true;
				if (this->currentAmmo > 0) {
					//Vector3 view = (cam->target - cam->position).Normalized();
					Entity* bullet = new Bullet(scene, PLAYERBULLET, view * 100.f, "bullet");
					bullet->getEntityData()->Translate.Set(plrPos.x, plrPos.y + 2, plrPos.z);
					bullet->getEntityData()->Scale.Set(0.1, 0.1, 0.1);
					// new function to spawn bullet at a scene's emanager, take in emanager as a refernce in this function to push back a bullet
					eManager->spawnMovingEntity(bullet);
					shoot = true;

					if (Game::inv.getActiveWeapon()->getWeaponType() == PISTOL)
					{
						AudioHandler::getEngine()->play3D(
							AudioHandler::getSoundSource(SOUNDTYPE::GUN_PISTOL_SHOOT),
							AudioHandler::to_vec3df(Vector3(0, 0, 0)),
							LOOPED::NOLOOP);
					}
					else
					{
						AudioHandler::getEngine()->play3D(
							AudioHandler::getSoundSource(SOUNDTYPE::GUN_SILENCER_SHOOT),
							AudioHandler::to_vec3df(Vector3(0, 0, 0)),
							LOOPED::NOLOOP);
					}

					DEBUG_MSG("shot");
					DEBUG_MSG("x: " << view.x << " y: " << view.y << " z: " << view.z);
					this->currentAmmo--; //minus current gun ammo
				}
				else {
					AudioHandler::getEngine()->play3D(
						AudioHandler::getSoundSource(SOUNDTYPE::GUN_PISTOL_EMPTY),
						AudioHandler::to_vec3df(Vector3(0, 0, 0)),
						LOOPED::NOLOOP);
				}
			}
			else if (!Application::IsMousePressed(0)) shoot = false;

			if (Application::IsKeyPressed('R') && !Reload && this->currentAmmo != this->magazineSize && Game::ammo > 0) {
				//start reload
				Reload = true;
				AudioHandler::getEngine()->play3D(
					AudioHandler::getSoundSource(SOUNDTYPE::GUN_PISTOL_RELOAD),
					AudioHandler::to_vec3df(Vector3(0, 0, 0)),
					LOOPED::NOLOOP);
			}

			if (Reload)
				reloadTillTime += dt; //start timer
			else
				reloadTillTime = 0;

			if (reloadTillTime > 1) //after 1 seconds, reload complete
			{
				if (Game::ammo < this->magazineSize)
				{
					int reloadAmmo = this->magazineSize - this->currentAmmo; //get amt to reload
					int TotalAmmo = Game::ammo;
					if (Game::activeScene == S_GUARD) {
						reloadAmmo = 10;
						TotalAmmo = 10;
					}
					if (reloadAmmo < TotalAmmo) //check if amount to reload is lesser than total ammo
					{
						this->currentAmmo += reloadAmmo; //if yes, minus reloadAmmo
						if (Game::activeScene != S_GUARD) //if not in guard scene (want it to be inf)
							Game::ammo -= reloadAmmo;
						Reload = false;
					}
					else
					{
						this->currentAmmo += TotalAmmo; //else reload total ammo, which means use all remaining total ammo
						if (Game::activeScene != S_GUARD) //if not in guard scene (want it to be inf)
							Game::ammo -= TotalAmmo;
						Reload = false;
					}
				}
				else
				{
					int reloadAmmo = this->magazineSize - this->currentAmmo; //get amt to reload
					this->currentAmmo += reloadAmmo; //add the reload amt to current gun ammo
					if (Game::activeScene != S_GUARD) //if not in guard scene (want it to be inf)
						Game::ammo -= reloadAmmo;
					Reload = false;
				}
			}
			Game::uiManager.getByTypeBM(UI_GENERAL)->getButtonByName("AmmoCount")->setText(std::to_string(this->currentAmmo) + "/" + std::to_string(this->magazineSize));
			Game::uiManager.getByTypeBM(UI_GENERAL)->getButtonByName("TotalAmmoCount")->setText(std::to_string(Game::ammo));
			Game::uiManager.getByTypeBM(UI_GENERAL)->getButtonByName("AmmoCount")->enable();
			Game::uiManager.getByTypeBM(UI_GENERAL)->getButtonByName("TotalAmmoCount")->enable();
		}
		
	}
	else
	{
		Game::uiManager.getByTypeBM(UI_GENERAL)->getButtonByName("AmmoCount")->disable();
		Game::uiManager.getByTypeBM(UI_GENERAL)->getButtonByName("TotalAmmoCount")->disable();
	}
}

/******************************************************************************/
/*!
\brief
Init weapon function that initalise parameters
*/
/******************************************************************************/
void Weapon::initWeapon(WEAPON_TYPE wType, int damages, int magSize)
{
	this->weaponType = wType;
	this->damage = damages;
	this->magazineSize = magSize;
	this->currentAmmo = magSize;
}

/******************************************************************************/
/*!
\brief
Return MeshType for UI
*/
/******************************************************************************/
GEOMETRY_TYPE Weapon::getMeshType()
{
	return associatedMeshType;
}

/******************************************************************************/
/*!
\brief
Return current weapon type
*/
/******************************************************************************/
WEAPON_TYPE Weapon::getWeaponType()
{
	if (this != nullptr)
		return this->weaponType;
}

/******************************************************************************/
/*!
\brief
Return current weapon ammo
*/
/******************************************************************************/
int Weapon::getWeaponAmmo()
{
	return this->currentAmmo;
}

/******************************************************************************/
/*!
\brief
Set UI cooldown function
*/
/******************************************************************************/
void Weapon::setUIcooldown(double d)
{
	if (this != nullptr)
		this->UIcooldown = d;
}

/******************************************************************************/
/*!
\brief
Get UI cooldown function
*/
/******************************************************************************/
double Weapon::getUIcooldown()
{
	if (this != nullptr)
		return this->UIcooldown;
}

int Weapon::getDamage()
{
	return this->damage;
}
