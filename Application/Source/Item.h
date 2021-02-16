#pragma once
enum ITEM_TYPE
{
	EMPTY,
	BURGER,
	CORN,
	EGGPLANT,
};

class Item
{
private:
	ITEM_TYPE itemType;
public:
	Item(ITEM_TYPE type);
	~Item();

	//Getter
	ITEM_TYPE getType();
};

