#pragma once
#include "Inventoryslot.h"
#include "Item.h"
#include <vector>

class MousePointer;

class ItemManager
{
public:
	ItemManager();
	~ItemManager();

	static void setMousePointer(MousePointer* mouseP);

	Item* makeItem(size_t ID);

private:
	std::vector<Item*> mItems;
};