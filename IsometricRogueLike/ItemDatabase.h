#pragma once
#include "Item.h"
#include <map>
#include <vector>

class ItemDatabase
{
private:
	ItemDatabase();
public:
	struct ItemContents
	{
		std::string name, desc, texFile;
		size_t iType, eqSlot;
		int prop[Item::NrProperties];
		int value;
	};

	static ItemDatabase& getInstance();

	ItemDatabase(const ItemDatabase&) = delete;
	ItemDatabase& operator=(const ItemDatabase&) = delete;
	~ItemDatabase();

	const ItemContents getItem(size_t ID) const;

private:
	std::map<size_t, ItemContents> mItemDatabase;
};