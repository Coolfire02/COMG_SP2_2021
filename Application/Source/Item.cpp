#include "Item.h"

Item::Item()
{
	this->itemType = EMPTY;
}

Item::Item(ITEM_TYPE type)
{
	this->itemType = type;
}

Item::~Item()
{
}

void Item::setType(ITEM_TYPE type)
{
	this->itemType = type;
}

ITEM_TYPE Item::getType()
{
	return this->itemType;
}
