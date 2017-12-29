#pragma once
#include "Inventoryslot.h"
#include <set>
#include <stack>

class Item;
class MousePointer;

class ItemManager
{
public:
	ItemManager();
	~ItemManager();

	static void setMousePointer(MousePointer* mouseP);

	Item* makeItem(size_t ID);

private:
	std::set<Item*> mItems;
};