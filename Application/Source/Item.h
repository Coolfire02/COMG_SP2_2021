#pragma once
/******************************************************************************/
/*!
\file	Item.h
\author Ridwan
\brief Header file containing the Item Class.
*/
/******************************************************************************/

//Item class created by Ridwan on 16/2/2021
//Inventory class optimized by Ridwan on 17/2/2021

/******************************************************************************/
/*!
\file	Item.h
\author Ridwan
\brief
Item System for the Game.
*/
/******************************************************************************/

//Define Item Types
enum ITEM_TYPE 
{
	BURGER = 0,
	CORN,
	EGGPLANT,
	ITEM_AMOUNT,
};

/******************************************************************************/
/*!
		Class Item:
\brief Item System for the Game.
*/
/******************************************************************************/
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

