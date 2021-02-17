#pragma once
enum ITEM_TYPE
{
	EMPTY = 0,
	BURGER,
	CORN,
	EGGPLANT,
};

class Item
{
private:
	ITEM_TYPE itemType;
public:
	Item();
	Item(ITEM_TYPE type);
	~Item();

	//Setter
	void setType(ITEM_TYPE type);

	//Getter
	ITEM_TYPE getType();
};

