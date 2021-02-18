#pragma once
enum ITEM_TYPE
{
	BURGER = 0,
	CORN,
	EGGPLANT,
};

class Item
{
private:
	ITEM_TYPE itemType;
	int amtOfItems;
public:
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

