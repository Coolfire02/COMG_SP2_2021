#include "Item.h"

Item::Item()
{
}

Item::Item(ITEM_TYPE type, int amt)
{
	this->itemType = type;
	this->amtOfItems = amt;
}

Item::~Item()
{
}

void Item::setType(ITEM_TYPE type)
{
	this->itemType = type;
}

void Item::setAmt(int amt)
{
	this->amtOfItems = amt;
}

ITEM_TYPE Item::getType()
{
	return this->itemType;
}

int Item::getAmt()
{
	return this->amtOfItems;
}
