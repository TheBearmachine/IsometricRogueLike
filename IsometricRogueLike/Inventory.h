#pragma once

class Item;

class Inventory
{
public:
    Inventory();
    ~Inventory();

    void populateContents(size_t size);
    size_t getSize() const;

    // Returns false if there is no free space
    bool insertItem(Item* item);
    Item* switchItemsInSlot(Item* newItem, size_t ID);
    Item** getItem(size_t ID);

private:
    size_t mSize;
    Item* mContents[64];
    int mNextFreeSlot;
};