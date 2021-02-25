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
	if (garageInv.empty()) //If player does not have any item yet
	{
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

void Inventory::switchCar(int cartype)
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

GarageInventory* Inventory::getCurrentCar()
{
	if (currentCar != nullptr)
		return this->currentCar;
	else
		return nullptr;
}

std::vector<GarageInventory*> Inventory::getGarageVector()
{
	return this->garageInv;
}

ItemInventory* Inventory::getItemInventory()
{
	return this->itemInventory;
}

WeaponInventory* Inventory::getWeaponInventory() {
	return this->weaponInv;
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
			return itemInventory->getCurrentItemType();
}

void Inventory::Update(double dt)
{
	//For General UI
	//Items
	if (itemInventory->getCurrentItem() != nullptr)
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
		default:
			Game::uiManager.getbManagerArray(UI_GENERAL)->getButtonByName("UIItem")->setQuadImage(UI_EMPTY);
			break;
		}
		Game::uiManager.getbManagerArray(UI_GENERAL)->getButtonByName("UIItem")->enable();
		Game::uiManager.getbManagerArray(UI_GENERAL)->getButtonByName("UIItemCurrent")->enable();
		Game::uiManager.getbManagerArray(UI_GENERAL)->getButtonByName("UIItemAmount")->setText(std::to_string(itemInventory->getCurrentItemAmt()));
		Game::uiManager.getbManagerArray(UI_GENERAL)->getButtonByName("UIItemAmount")->enable();
	}
	else
		Game::uiManager.getbManagerArray(UI_GENERAL)->getButtonByName("UIItemAmount")->disable();

	//Weapons
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

	//For Item Inventory UI
	if (itemInventory->getCurrentItem() == nullptr) //If there is no Item Inventory
	{
		for (int i = 0; i < ITEM_AMOUNT; i++)
		{
			Game::uiManager.getbManagerArray(UI_ITEM_INVENTORY)->getButtonByName("UIItemInventorySlot" + std::to_string(i + 1))->disable();
			Game::uiManager.getbManagerArray(UI_ITEM_INVENTORY)->getButtonByName("UIItemInventorySlotCurrent" + std::to_string(i + 1))->disable();
		}
		Game::uiManager.getbManagerArray(UI_ITEM_INVENTORY)->getButtonByName("UIItemsInventoryCurrent")->disable();
		Game::uiManager.getbManagerArray(UI_ITEM_INVENTORY)->getButtonByName("UIItemsInventoryCurrentBorder")->disable();
		Game::uiManager.getbManagerArray(UI_ITEM_INVENTORY)->getButtonByName("UIItemsInventoryName")->disable();
	}
	else if (itemInventory->getItemVect().size() > 0) //If item is owned at least once, then display
	{
		for (int i = 0; i < itemInventory->getItemVect().size(); i++)
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
				Game::uiManager.getbManagerArray(UI_ITEM_INVENTORY)->getButtonByName("UIItemsInventoryCurrent")->setQuadImage(UI_BLANK);
				Game::uiManager.getbManagerArray(UI_ITEM_INVENTORY)->getButtonByName("UIItemsInventoryName")->setText(" ");
				break;
			}
		}
		for (int i = 0; i < ITEM_AMOUNT; i++)
		{
			//Disable all non-current item UIs
			if (itemInventory->getCurrentItem()->getType() != i)
				Game::uiManager.getbManagerArray(UI_ITEM_INVENTORY)->getButtonByName("UIItemInventorySlotCurrent" + std::to_string(i + 1))->disable();
			else
				Game::uiManager.getbManagerArray(UI_ITEM_INVENTORY)->getButtonByName("UIItemInventorySlotCurrent" + std::to_string(i + 1))->enable();
			switch (itemInventory->getCurrentItemType())
			{
			case BURGER:
				Game::uiManager.getbManagerArray(UI_ITEM_INVENTORY)->getButtonByName("UIItemsInventoryCurrent")->setQuadImage(UI_BURGER);
				Game::uiManager.getbManagerArray(UI_ITEM_INVENTORY)->getButtonByName("UIItemsInventoryName")->setText("Burger\nAmount:\n" + std::to_string(itemInventory->getCurrentItemAmt()));
				break;
			case CORN:
				Game::uiManager.getbManagerArray(UI_ITEM_INVENTORY)->getButtonByName("UIItemsInventoryCurrent")->setQuadImage(UI_CORN);
				Game::uiManager.getbManagerArray(UI_ITEM_INVENTORY)->getButtonByName("UIItemsInventoryName")->setText("Corn\nAmount:\n" + std::to_string(itemInventory->getCurrentItemAmt()));
				break;
			case EGGPLANT:
				Game::uiManager.getbManagerArray(UI_ITEM_INVENTORY)->getButtonByName("UIItemsInventoryCurrent")->setQuadImage(UI_EGGPLANT);
				Game::uiManager.getbManagerArray(UI_ITEM_INVENTORY)->getButtonByName("UIItemsInventoryName")->setText("Eggplant\nAmount:\n" + std::to_string(itemInventory->getCurrentItemAmt()));
				break;
			}
		}
		
	}
	else //Do not display any item slots as no items owned
	{
		for (int i = 0; i < ITEM_AMOUNT; i++)
		{
			Game::uiManager.getbManagerArray(UI_ITEM_INVENTORY)->getButtonByName("UIItemInventorySlot" + std::to_string(i + 1))->disable();
			Game::uiManager.getbManagerArray(UI_ITEM_INVENTORY)->getButtonByName("UIItemInventorySlotCurrent" + std::to_string(i + 1))->disable();
		}
		Game::uiManager.getbManagerArray(UI_ITEM_INVENTORY)->getButtonByName("UIItemsInventoryCurrent")->disable();
		Game::uiManager.getbManagerArray(UI_ITEM_INVENTORY)->getButtonByName("UIItemsInventoryCurrentBorder")->disable();
		Game::uiManager.getbManagerArray(UI_ITEM_INVENTORY)->getButtonByName("UIItemsInventoryName")->disable();
	}

	//For Weapon Inventory
	if (weaponInv->getActiveWeapon() == nullptr && weaponInv->getWeaponList().empty()) //If there is no Item Inventory
	{
		for (int i = 0; i < WEAPON_COUNT; i++)
		{
			Game::uiManager.getbManagerArray(UI_WEAPON_INVENTORY)->getButtonByName("UIWeaponInventorySlot" + std::to_string(i + 1))->disable();
			Game::uiManager.getbManagerArray(UI_WEAPON_INVENTORY)->getButtonByName("UIWeaponInventorySlotCurrent" + std::to_string(i + 1))->disable();
		}
		Game::uiManager.getbManagerArray(UI_WEAPON_INVENTORY)->getButtonByName("UIWeaponsInventoryCurrent")->disable();
		Game::uiManager.getbManagerArray(UI_WEAPON_INVENTORY)->getButtonByName("UIWeaponsInventoryCurrentBorder")->disable();
		Game::uiManager.getbManagerArray(UI_WEAPON_INVENTORY)->getButtonByName("UIWeaponsInventoryName")->disable();
	}
	else if (weaponInv->getWeaponList().size() > 0) //If item is owned at least once, then display
	{
		if (weaponInv->getActiveWeapon() == nullptr)
			Game::uiManager.getbManagerArray(UI_WEAPON_INVENTORY)->getButtonByName("UIWeaponsInventoryCurrentBorder")->disable();
		else
			Game::uiManager.getbManagerArray(UI_WEAPON_INVENTORY)->getButtonByName("UIWeaponsInventoryCurrentBorder")->enable();

		for (int i = 0; i < WEAPON_COUNT; i++)
		{
			if (i <= (weaponInv->getWeaponList().size() - 1))
			{
				switch (weaponInv->getWeaponList()[i]->getWeaponType())
				{
				case PISTOL:
					Game::uiManager.getbManagerArray(UI_WEAPON_INVENTORY)->getButtonByName("UIWeaponInventorySlot" + std::to_string(i + 1))->setQuadImage(UI_PISTOL);
					break;
				case SILENCER:
					Game::uiManager.getbManagerArray(UI_WEAPON_INVENTORY)->getButtonByName("UIWeaponInventorySlot" + std::to_string(i + 1))->setQuadImage(UI_SILENCER);
					break;
				default:
					Game::uiManager.getbManagerArray(UI_WEAPON_INVENTORY)->getButtonByName("UIWeaponInventorySlot" + std::to_string(i + 1))->setQuadImage(UI_BLANK);
					Game::uiManager.getbManagerArray(UI_WEAPON_INVENTORY)->getButtonByName("UIWeaponsInventoryCurrent")->setQuadImage(UI_BLANK);
					Game::uiManager.getbManagerArray(UI_WEAPON_INVENTORY)->getButtonByName("UIWeaponsInventoryName")->setText(" ");
					break;
				}
			}
			else
			{
				Game::uiManager.getbManagerArray(UI_WEAPON_INVENTORY)->getButtonByName("UIWeaponInventorySlot" + std::to_string(i + 1))->setQuadImage(UI_BLANK);
				Game::uiManager.getbManagerArray(UI_WEAPON_INVENTORY)->getButtonByName("UIWeaponsInventoryCurrent")->setQuadImage(UI_BLANK);
				Game::uiManager.getbManagerArray(UI_WEAPON_INVENTORY)->getButtonByName("UIWeaponsInventoryName")->setText(" ");
			}
		}
		for (int i = 0; i < WEAPON_COUNT; i++)
			Game::uiManager.getbManagerArray(UI_WEAPON_INVENTORY)->getButtonByName("UIWeaponInventorySlotCurrent" + std::to_string(i + 1))->disable();

		for (int i = 0; i < weaponInv->getWeaponList().size(); i++)
		{
			//Disable all non-current item UIs
			if (weaponInv->getActiveWeapon()->getWeaponType() == weaponInv->getWeaponList()[i]->getWeaponType())
				Game::uiManager.getbManagerArray(UI_WEAPON_INVENTORY)->getButtonByName("UIWeaponInventorySlotCurrent" + std::to_string(i + 1))->enable();

			//if (weaponInv->getActiveWeapon()->getWeaponType() == i)
			//	Game::uiManager.getbManagerArray(UI_WEAPON_INVENTORY)->getButtonByName("UIWeaponInventorySlotCurrent" + std::to_string(i + 1))->disable();
			//else
			//	Game::uiManager.getbManagerArray(UI_WEAPON_INVENTORY)->getButtonByName("UIWeaponInventorySlotCurrent" + std::to_string(i + 1))->enable();
			switch (weaponInv->getActiveWeapon()->getWeaponType())
			{
			case PISTOL:
				Game::uiManager.getbManagerArray(UI_WEAPON_INVENTORY)->getButtonByName("UIWeaponsInventoryCurrent")->setQuadImage(UI_PISTOL);
				Game::uiManager.getbManagerArray(UI_WEAPON_INVENTORY)->getButtonByName("UIWeaponsInventoryName")->setText("Pistol\nAmmo:\n" + std::to_string(weaponInv->getActiveWeapon()->getWeaponAmmo()));
				break;
			case SILENCER:
				Game::uiManager.getbManagerArray(UI_WEAPON_INVENTORY)->getButtonByName("UIWeaponsInventoryCurrent")->setQuadImage(UI_SILENCER);
				Game::uiManager.getbManagerArray(UI_WEAPON_INVENTORY)->getButtonByName("UIWeaponsInventoryName")->setText("Silencer\nAmmo:\n" + std::to_string(weaponInv->getActiveWeapon()->getWeaponAmmo()));
				break;
			}
		}

	}
	else //Do not display any item slots as no items owned
	{
		for (int i = 0; i < WEAPON_COUNT; i++)
		{
			Game::uiManager.getbManagerArray(UI_WEAPON_INVENTORY)->getButtonByName("UIWeaponInventorySlot" + std::to_string(i + 1))->disable();
			Game::uiManager.getbManagerArray(UI_WEAPON_INVENTORY)->getButtonByName("UIWeaponInventorySlotCurrent" + std::to_string(i + 1))->disable();
		}
		Game::uiManager.getbManagerArray(UI_WEAPON_INVENTORY)->getButtonByName("UIWeaponsInventoryCurrent")->disable();
		Game::uiManager.getbManagerArray(UI_WEAPON_INVENTORY)->getButtonByName("UIWeaponsInventoryCurrentBorder")->disable();
		Game::uiManager.getbManagerArray(UI_WEAPON_INVENTORY)->getButtonByName("UIWeaponsInventoryName")->disable();
	}

	//For Garage Inventory UI
	if (currentCar == nullptr) //If there is no Garage Inventory
	{
		for (int i = 0; i < CAR_COUNT; i++)
		{
			Game::uiManager.getbManagerArray(UI_GARAGE_INVENTORY)->getButtonByName("UIGarageInventorySlot" + std::to_string(i + 1))->disable();
			Game::uiManager.getbManagerArray(UI_GARAGE_INVENTORY)->getButtonByName("UIGarageInventorySlotCurrent" + std::to_string(i + 1))->disable();
		}
		Game::uiManager.getbManagerArray(UI_GARAGE_INVENTORY)->getButtonByName("UIGarageInventoryCurrent")->disable();
		Game::uiManager.getbManagerArray(UI_GARAGE_INVENTORY)->getButtonByName("UIGarageInventoryCurrentBorder")->disable();
		Game::uiManager.getbManagerArray(UI_GARAGE_INVENTORY)->getButtonByName("UIGarageInventoryName")->disable();
	}
	else if (garageInv.size() > 0) //If item is owned at least once, then display
	{
		for (int i = 0; i < garageInv.size(); i++)
		{
			switch (garageInv[i]->getCarType())
			{
			case SEDAN:
				Game::uiManager.getbManagerArray(UI_GARAGE_INVENTORY)->getButtonByName("UIGarageInventorySlot" + std::to_string(i + 1))->setQuadImage(UI_SEDAN);
				break;
			case SEDAN_SPORTS:
				Game::uiManager.getbManagerArray(UI_GARAGE_INVENTORY)->getButtonByName("UIGarageInventorySlot" + std::to_string(i + 1))->setQuadImage(UI_SEDAN_SPORTS);
				break;
			case RACER:
				Game::uiManager.getbManagerArray(UI_GARAGE_INVENTORY)->getButtonByName("UIGarageInventorySlot" + std::to_string(i + 1))->setQuadImage(UI_RACER);
				break;
			case POLICE:
				Game::uiManager.getbManagerArray(UI_GARAGE_INVENTORY)->getButtonByName("UIGarageInventorySlot" + std::to_string(i + 1))->setQuadImage(UI_POLICE);
				break;
			case AMBULANCE:
				Game::uiManager.getbManagerArray(UI_GARAGE_INVENTORY)->getButtonByName("UIGarageInventorySlot" + std::to_string(i + 1))->setQuadImage(UI_AMBULANCE);
				break;
			case SUV:
				Game::uiManager.getbManagerArray(UI_GARAGE_INVENTORY)->getButtonByName("UIGarageInventorySlot" + std::to_string(i + 1))->setQuadImage(UI_SUV);
				break;
			default:
				Game::uiManager.getbManagerArray(UI_GARAGE_INVENTORY)->getButtonByName("UIGarageInventorySlot" + std::to_string(i + 1))->setQuadImage(UI_BLANK);
				Game::uiManager.getbManagerArray(UI_GARAGE_INVENTORY)->getButtonByName("UIGarageInventoryCurrent")->setQuadImage(UI_BLANK);
				Game::uiManager.getbManagerArray(UI_GARAGE_INVENTORY)->getButtonByName("UIGarageInventoryName")->setText(" ");
				break;
			}
		}
		for (int i = 0; i < CAR_COUNT; i++)
			Game::uiManager.getbManagerArray(UI_GARAGE_INVENTORY)->getButtonByName("UIGarageInventorySlotCurrent" + std::to_string(i + 1))->disable();

		for (int i = 0; i < garageInv.size(); i++)
		{
			//Disable all non-current item UIs
			if (currentCar->getCarType() == garageInv[i]->getCarType())
				Game::uiManager.getbManagerArray(UI_GARAGE_INVENTORY)->getButtonByName("UIGarageInventorySlotCurrent" + std::to_string(i + 1))->enable();

			switch (currentCar->getCarType())
			{
			case SEDAN:
				Game::uiManager.getbManagerArray(UI_GARAGE_INVENTORY)->getButtonByName("UIGarageInventoryCurrent")->setQuadImage(UI_SEDAN);
				Game::uiManager.getbManagerArray(UI_GARAGE_INVENTORY)->getButtonByName("UIGarageInventoryName")->setText("Sedan\nSpeed:\n" + currentCar->getMaxCarSpd(SEDAN) + "km/h");
				break;
			case SEDAN_SPORTS:
				Game::uiManager.getbManagerArray(UI_GARAGE_INVENTORY)->getButtonByName("UIGarageInventoryCurrent")->setQuadImage(UI_SEDAN_SPORTS);
				Game::uiManager.getbManagerArray(UI_GARAGE_INVENTORY)->getButtonByName("UIGarageInventoryName")->setText("Sedan Sports\nSpeed:\n" + currentCar->getMaxCarSpd(SEDAN_SPORTS) + "km/h");
				break;
			case RACER:
				Game::uiManager.getbManagerArray(UI_GARAGE_INVENTORY)->getButtonByName("UIGarageInventoryCurrent")->setQuadImage(UI_RACER);
				Game::uiManager.getbManagerArray(UI_GARAGE_INVENTORY)->getButtonByName("UIGarageInventoryName")->setText("Racer\nSpeed:\n" + currentCar->getMaxCarSpd(RACER) + "km/h");
				break;
			case POLICE:
				Game::uiManager.getbManagerArray(UI_GARAGE_INVENTORY)->getButtonByName("UIGarageInventoryCurrent")->setQuadImage(UI_POLICE);
				Game::uiManager.getbManagerArray(UI_GARAGE_INVENTORY)->getButtonByName("UIGarageInventoryName")->setText("Police\nSpeed:\n" + currentCar->getMaxCarSpd(POLICE) + "km/h");
				break;
			case AMBULANCE:
				Game::uiManager.getbManagerArray(UI_GARAGE_INVENTORY)->getButtonByName("UIGarageInventoryCurrent")->setQuadImage(UI_AMBULANCE);
				Game::uiManager.getbManagerArray(UI_GARAGE_INVENTORY)->getButtonByName("UIGarageInventoryName")->setText("Ambulance\nSpeed:\n" + currentCar->getMaxCarSpd(AMBULANCE) + "km/h");
				break;
			case SUV:
				Game::uiManager.getbManagerArray(UI_GARAGE_INVENTORY)->getButtonByName("UIGarageInventoryCurrent")->setQuadImage(UI_SUV);
				Game::uiManager.getbManagerArray(UI_GARAGE_INVENTORY)->getButtonByName("UIGarageInventoryName")->setText("SUV\nSpeed:\n" + currentCar->getMaxCarSpd(SUV) + "km/h");
				break;
			}
		}

	}
	else //Do not display any item slots as no items owned
	{
		for (int i = 0; i < CAR_COUNT; i++)
		{
			Game::uiManager.getbManagerArray(UI_GARAGE_INVENTORY)->getButtonByName("UIGarageInventorySlot" + std::to_string(i + 1))->disable();
			Game::uiManager.getbManagerArray(UI_GARAGE_INVENTORY)->getButtonByName("UIGarageInventorySlotCurrent" + std::to_string(i + 1))->disable();
		}
		Game::uiManager.getbManagerArray(UI_GARAGE_INVENTORY)->getButtonByName("UIGarageInventoryCurrent")->disable();
		Game::uiManager.getbManagerArray(UI_GARAGE_INVENTORY)->getButtonByName("UIGarageInventoryCurrentBorder")->disable();
		Game::uiManager.getbManagerArray(UI_GARAGE_INVENTORY)->getButtonByName("UIGarageInventoryName")->disable();
	}

	toggleTimer += dt;
	if (Application::IsKeyPressed('E')) //pick up weapon
		addWeap(PISTOL);
	if (Application::IsKeyPressed('F')) //pick up weapon
	{
		addItem(BURGER, 1);
		addItem(CORN, 2);
		addItem(EGGPLANT, 3);

		addWeap(SILENCER);

		addCar(SEDAN);

		addCar(POLICE);
		addCar(RACER);

		addCar(SUV);
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