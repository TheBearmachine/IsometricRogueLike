#include "Inventory.h"
#include "Item.h"

Inventory::Inventory() :
	mSize(0)
{

}

Inventory::~Inventory()
{

}

void Inventory::populateContents(size_t size)
{
	if (mSize != 0)
	{
		for (size_t i = 0; i < size; i++)
		{
			mContents[i] = nullptr;
		}
	}
	mSize = size;
}

size_t Inventory::getSize() const
{
	return mSize;
}

Item* Inventory::switchItemsInSlot(Item* newItem, size_t ID)
{
	if (ID >= mSize && ID < 0)
	{
		printf("Error, slot ID out of range! Valid range is 0 to %u.\n", mSize);
		return newItem;
	}
	Item* temp = mContents[ID];
	mContents[ID] = newItem;
	if (newItem)
		newItem->setAttachment(mContents[ID]);
	return temp;
}

Item ** Inventory::getItem(size_t ID)
{
	if (ID >= mSize && ID < 0)
	{
		printf("Error, slot ID out of range! Valid range is 0 to %u.\n", mSize);
		return nullptr;
	}
	return &mContents[ID];
}
