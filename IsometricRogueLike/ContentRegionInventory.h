#pragma once
#include "ContentRegion.h"
#include "Inventoryslot.h"

class Inventory;

class ContentRegionInventory : public ContentRegion
{
public:
	ContentRegionInventory();
	ContentRegionInventory(Inventory* refInv, size_t slotsPerRow);
	~ContentRegionInventory();

	void createNewSlots(size_t size, size_t slotsPerRow);

	Inventoryslot* getInventorySlot(size_t ID);

	void setInvSlotListener(IInventoryslotListener* listener);

	virtual bool delegateEvent(const sf::Event &_event) override;

	virtual void drawPrep(DrawingManager* drawingMan) override;
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

private:
	Inventoryslot* mInventoryslots;
	Inventory* mInvRef;
	size_t mSlotsNr;
};