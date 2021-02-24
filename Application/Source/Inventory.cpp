#include "Inventory.h"
#include "Application.h"

Inventory::Inventory()
{
	currentCar = nullptr;

	//Create garage inventory
	currentCar = new GarageInventory(SEDAN);
	garageInv.push_back(currentCar);

	//For item inventory
	itemInventory = new ItemInventory();
	//addItem(BURGER, 0);

	//for weapon inven
	weaponInv = nullptr;
	addWeap(SILENCER);
}

Inventory::~Inventory()
{
}

void Inventory::addWeap(WEAPON_TYPE weaponType)
{
	if (weaponInv == nullptr)
		weaponInv = new WeaponInventory(weaponType);
	else
		weaponInv->addWeapon(weaponType);
}

void Inventory::addCar(CAR_TYPE cartype)
{
	if (garageInv[0] == nullptr) //If player does not have any item yet
	{
		garageInv.clear();
		currentCar = new GarageInventory(cartype);
		garageInv.push_back(currentCar);
	}
	for (int i = 0; i < garageInv.size(); i++) //If player owns car already
	{
		if (garageInv[i]->getCarType() == cartype)
		{
			return;
		}
	}
	GarageInventory* addingCar; //If player does not own a specific car yet
	addingCar = new GarageInventory(cartype);
	garageInv.push_back(addingCar);
}

void Inventory::addItem(ITEM_TYPE itemtype, int amt)
{
	if (itemInventory == nullptr) //If player does not have any item yet
	{
		itemInventory = new ItemInventory(itemtype, amt);
	}
	else
	{
		itemInventory->addItem(itemtype, amt);
	}
}

void Inventory::changeItemAmt(ITEM_TYPE itemtype, int amt)
{
	if (itemInventory != nullptr)
		itemInventory->setAmtOfItems(itemtype, amt);
	return;
}

void Inventory::deleteWeapon(WEAPON_TYPE wType)
{
	this->weaponInv->delWeapon(wType);
}

void Inventory::switchCar(CAR_TYPE cartype)
{
	for (int i = 0; i < garageInv.size(); i++)
	{
		if (garageInv[i]->getCarType() == cartype)
		{
			currentCar = garageInv[i];
			return;
		}
	}
}

void Inventory::switchWeapon(int index)
{
	weaponInv->switchActiveWeapon(index);
}

void Inventory::toggleItem()
{
	if (itemInventory != nullptr)
		itemInventory->toggleItem();
	return;
}

void Inventory::getGarageInventory()
{
	//blank for now
}

ItemInventory* Inventory::getItemInventory()
{
	return this->itemInventory;
}

std::vector<Weapon*> Inventory::getWeaponVector()
{
	return weaponInv->getWeaponList();
}

std::vector<Item*> Inventory::getItemVector()
{
	return itemInventory->getItemVect();
}

CAR_TYPE Inventory::getCurrentCarType()
{
	return currentCar->getCarType();
}

ITEM_TYPE Inventory::getCurrentItemType()
{
	if (itemInventory != nullptr)
		if (itemInventory->getCurrentItem() != nullptr)
			return itemInventory->getCurrenItemType();
}

void Inventory::Update(double dt)
{
	switch (getCurrentItemType())
	{
	case BURGER:
		Game::uiManager.getbManagerArray(UI_GENERAL)->getButtonByName("UIItem")->setQuadImage(UI_BURGER);
		break;
	case CORN:
		Game::uiManager.getbManagerArray(UI_GENERAL)->getButtonByName("UIItem")->setQuadImage(UI_CORN);
		break;
	case EGGPLANT:
		Game::uiManager.getbManagerArray(UI_GENERAL)->getButtonByName("UIItem")->setQuadImage(UI_EGGPLANT);
		break;
	}

	if (weaponInv->getActiveWeapon() == nullptr)
	{
		for (int i = 0; i < WEAPON_COUNT; i++)
		{
			Game::uiManager.getbManagerArray(UI_GENERAL)->getButtonByName("UIWeaponCurrent" + std::to_string(i + 1))->disable();
		}
	}
	else if (weaponInv->getWeaponList().size() > 0)
	{
		//display first gun slot
		Game::uiManager.getbManagerArray(UI_GENERAL)->getButtonByName("Weapon1")->enable();
		Game::uiManager.getbManagerArray(UI_GENERAL)->getButtonByName("Weapon2")->disable();

		Game::uiManager.getbManagerArray(UI_GENERAL)->getButtonByName("UIWeaponCurrent1")->enable();
		Game::uiManager.getbManagerArray(UI_GENERAL)->getButtonByName("UIWeaponCurrent2")->disable();
		switch (weaponInv->getWeaponList()[0]->getWeaponType())
		{
		case PISTOL:
			Game::uiManager.getbManagerArray(UI_GENERAL)->getButtonByName("Weapon1")->setQuadImage(UI_PISTOL);
			break;
		case SILENCER:
			Game::uiManager.getbManagerArray(UI_GENERAL)->getButtonByName("Weapon1")->setQuadImage(UI_SILENCER);
			break;
		}

		if (weaponInv->getWeaponList().size() == 2) //check if size is 2, then display second gun slot
		{
			Game::uiManager.getbManagerArray(UI_GENERAL)->getButtonByName("Weapon2")->enable();
			switch (weaponInv->getWeaponList()[1]->getWeaponType())
			{
			case PISTOL:
				Game::uiManager.getbManagerArray(UI_GENERAL)->getButtonByName("Weapon2")->setQuadImage(UI_PISTOL);
				break;
			case SILENCER:
				Game::uiManager.getbManagerArray(UI_GENERAL)->getButtonByName("Weapon2")->setQuadImage(UI_SILENCER);
				break;
			}
			if (weaponInv->getWeaponList()[1] == weaponInv->getActiveWeapon())
			{
				Game::uiManager.getbManagerArray(UI_GENERAL)->getButtonByName("UIWeaponCurrent1")->disable();
				Game::uiManager.getbManagerArray(UI_GENERAL)->getButtonByName("UIWeaponCurrent2")->enable();
			}
		}
	}
	else //do not display any gun slots as no guns owned
	{
		Game::uiManager.getbManagerArray(UI_GENERAL)->getButtonByName("Weapon1")->disable();
		Game::uiManager.getbManagerArray(UI_GENERAL)->getButtonByName("Weapon2")->disable();
		for (int i = 0; i < WEAPON_COUNT; i++)
		{
			Game::uiManager.getbManagerArray(UI_GENERAL)->getButtonByName("UIWeaponBorder" + std::to_string(i + 1))->disable();
			Game::uiManager.getbManagerArray(UI_GENERAL)->getButtonByName("UIWeaponCurrent" + std::to_string(i + 1))->disable();
		}
	}

	if (Game::uiManager.getCurrentMenu() == UI_ITEM_INVENTORY)
	{
		if (itemInventory->getCurrentItem() == nullptr)
		{
			for (int i = 0; i < ITEM_AMOUNT; i++)
			{
				Game::uiManager.getbManagerArray(UI_ITEM_INVENTORY)->getButtonByName("UIItemInventorySlot" + std::to_string(i + 1))->disable();
				Game::uiManager.getbManagerArray(UI_ITEM_INVENTORY)->getButtonByName("UIItemInventorySlotCurrent" + std::to_string(i + 1))->disable();
			}
		}
		else if (itemInventory->getItemVect().size() > 0)
		{
			for (int i = 0; i < itemInventory->getItemVect().size(); i++)
			{
				if (itemInventory->getItemVect()[i]->getAmt() == 0)
				{
					switch (itemInventory->getItemVect()[i]->getType())
					{
					case BURGER:
						Game::uiManager.getbManagerArray(UI_ITEM_INVENTORY)->getButtonByName("UIItemInventorySlot" + std::to_string(i + 1))->setQuadImage(UI_BURGER);
						break;
					case CORN:
						Game::uiManager.getbManagerArray(UI_ITEM_INVENTORY)->getButtonByName("UIItemInventorySlot" + std::to_string(i + 1))->setQuadImage(UI_CORN);
						break;
					case EGGPLANT:
						Game::uiManager.getbManagerArray(UI_ITEM_INVENTORY)->getButtonByName("UIItemInventorySlot" + std::to_string(i + 1))->setQuadImage(UI_EGGPLANT);
						break;
					default:
						Game::uiManager.getbManagerArray(UI_ITEM_INVENTORY)->getButtonByName("UIItemInventorySlot" + std::to_string(i + 1))->setQuadImage(UI_BLANK);
						break;
					}
				}
			}
			////display first gun slot
			//Game::uiManager.getbManagerArray(UI_GENERAL)->getButtonByName("Weapon1")->enable();
			//Game::uiManager.getbManagerArray(UI_GENERAL)->getButtonByName("Weapon2")->disable();

			//Game::uiManager.getbManagerArray(UI_GENERAL)->getButtonByName("UIWeaponCurrent1")->enable();
			//Game::uiManager.getbManagerArray(UI_GENERAL)->getButtonByName("UIWeaponCurrent2")->disable();
			//switch (weaponInv->getWeaponList()[0]->getWeaponType())
			//{
			//case PISTOL:
			//	Game::uiManager.getbManagerArray(UI_GENERAL)->getButtonByName("Weapon1")->setQuadImage(UI_PISTOL);
			//	break;
			//case SILENCER:
			//	Game::uiManager.getbManagerArray(UI_GENERAL)->getButtonByName("Weapon1")->setQuadImage(UI_SILENCER);
			//	break;
			//}

			//if (weaponInv->getWeaponList().size() == 2) //check if size is 2, then display second gun slot
			//{
			//	Game::uiManager.getbManagerArray(UI_GENERAL)->getButtonByName("Weapon2")->enable();
			//	switch (weaponInv->getWeaponList()[1]->getWeaponType())
			//	{
			//	case PISTOL:
			//		Game::uiManager.getbManagerArray(UI_GENERAL)->getButtonByName("Weapon2")->setQuadImage(UI_PISTOL);
			//		break;
			//	case SILENCER:
			//		Game::uiManager.getbManagerArray(UI_GENERAL)->getButtonByName("Weapon2")->setQuadImage(UI_SILENCER);
			//		break;
			//	}
			//	if (weaponInv->getWeaponList()[1] == weaponInv->getActiveWeapon())
			//	{
			//		Game::uiManager.getbManagerArray(UI_GENERAL)->getButtonByName("UIWeaponCurrent1")->disable();
			//		Game::uiManager.getbManagerArray(UI_GENERAL)->getButtonByName("UIWeaponCurrent2")->enable();
			//	}
			//}
		}
		else //do not display any gun slots as no guns owned
		{
			for (int i = 0; i < ITEM_AMOUNT; i++)
			{
				Game::uiManager.getbManagerArray(UI_ITEM_INVENTORY)->getButtonByName("UIItemInventorySlot" + std::to_string(i + 1))->disable();
				Game::uiManager.getbManagerArray(UI_ITEM_INVENTORY)->getButtonByName("UIItemInventorySlotCurrent" + std::to_string(i + 1))->disable();
			}
		}
		/*switch (getCurrentItemType())
		{
		case BURGER:
			Game::uiManager.getbManagerArray(UI_GENERAL)->getButtonByName("UIItem")->setQuadImage(UI_BURGER);
			break;
		case CORN:
			Game::uiManager.getbManagerArray(UI_GENERAL)->getButtonByName("UIItem")->setQuadImage(UI_CORN);
			break;
		case EGGPLANT:
			Game::uiManager.getbManagerArray(UI_GENERAL)->getButtonByName("UIItem")->setQuadImage(UI_EGGPLANT);
			break;
		}*/
		
	}


	toggleTimer += dt;
	if (Application::IsKeyPressed('E')) //pick up weapon
		addWeap(PISTOL);
	if (Application::IsKeyPressed('F')) //pick up weapon
	{
		addItem(BURGER, 1);
		addItem(CORN, 1);
		addItem(EGGPLANT, 1);

		addWeap(SILENCER);
	}
	if (GetAsyncKeyState('1') & 0x0001) //weapon slot 1
		switchWeapon(0);
	if (GetAsyncKeyState('2') & 0x0001) //weapon slot 2
		switchWeapon(1);
	if (GetAsyncKeyState('3') & 0x0001) //weapon slot 3
		switchWeapon(2);
	if (GetAsyncKeyState('4') & 0x0001) //weapon slot 4
		switchWeapon(3);
	if (toggleTimer > 1 && Application::IsKeyPressed('O')) //delete equipped weapon
	{
		toggleTimer = 0;
		deleteWeapon(getActiveWeapon()->getWeaponType());
	}
	if (toggleTimer > 1 && Application::IsKeyPressed('T')) //delete equipped weapon
	{
		toggleTimer = 0;
		toggleItem();
	}
}

int Inventory::getCurrentItemAmt()
{
	if (itemInventory != nullptr)
		return itemInventory->getCurrentItemAmt();
}

Weapon* Inventory::getActiveWeapon()
{
	if (weaponInv->getWeaponList().empty())
		return nullptr;
	else
		return weaponInv->getActiveWeapon();
}

WEAPON_TYPE Inventory::getCurrentWeaponType()
{
	if (weaponInv != nullptr)
		return weaponInv->getActiveWeapon()->getWeaponType();
}

//void Inventory::Update(Camera* cam, double dt) {
//	//itemInventory.Update();
//	weaponInv.update(cam, dt);
//}
