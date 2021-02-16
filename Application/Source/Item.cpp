#include "Item.h"

Item::Item(ITEM_TYPE type)
{
	this->itemType = type;
}

Item::~Item()
{
}

ITEM_TYPE Item::getType()
{
	return this->itemType;
}
