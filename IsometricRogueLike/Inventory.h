#pragma once

class Item;

class Inventory
{
public:
	Inventory();
	~Inventory();

	void populateContents(size_t size);
	size_t getSize() const;

	Item* switchItemsInSlot(Item* newItem, size_t ID);
	Item** getItem(size_t ID);

private:
	size_t mSize;
	Item* mContents[20];
};