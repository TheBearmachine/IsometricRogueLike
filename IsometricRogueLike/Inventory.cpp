#include "Inventory.h"
#include "Item.h"

Inventory::Inventory() :
	mSize(0),
	mNextFreeSlot(0)
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
	mNextFreeSlot = 0;
}

size_t Inventory::getSize() const
{
	return mSize;
}

bool Inventory::insertItem(Item * item)
{
	if (mNextFreeSlot == -1)
	{
		printf("No free slot in insert the item into.\n");
		return false;
	}

	switchItemsInSlot(item, mNextFreeSlot);

	return true;
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

	bool hasFreeSlot = false;
	for (int i = 0; i < mSize; i++)
	{
		if (!mContents[i])
		{
			mNextFreeSlot = i;
			hasFreeSlot = true;
			break;
		}
	}
	if (!hasFreeSlot)
		mNextFreeSlot = -1;

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
