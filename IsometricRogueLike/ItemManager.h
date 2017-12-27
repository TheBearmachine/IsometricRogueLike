#pragma once
#include "Inventoryslot.h"
#include <set>
#include <stack>

class Item;
class MousePointer;

class ItemManager: public IInventoryslotListener
{
public:
	ItemManager();
	~ItemManager();

	static void setMousePointer(MousePointer* mouseP);

	Item* makeItem(size_t ID);

	void buttonAction(Item* item, Inventoryslot* invSlot);

private:
	std::set<Item*> mItems;
};