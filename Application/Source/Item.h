#pragma once
//Item class created by Ridwan on 16/2/2021
//Inventory class optimized by Ridwan on 17/2/2021

//Define Item Types
enum ITEM_TYPE 
{
	BURGER = 0,
	CORN,
	EGGPLANT,
	EMPTY_ITEM,
	ITEM_AMOUNT,
};

class Item
{
private:
	//Store item type
	ITEM_TYPE itemType;

	//Amount of items
	int amtOfItems;
public:
	//Initialising
	Item();
	Item(ITEM_TYPE type, int amt);
	~Item();

	//Setter
	void setType(ITEM_TYPE type);
	void setAmt(int amt);

	//Getter
	ITEM_TYPE getType();
	int getAmt();
};

