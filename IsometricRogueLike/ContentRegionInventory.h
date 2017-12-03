#pragma once
#include "ContentRegion.h"
#include "Inventoryslot.h"

class ContentRegionInventory : public ContentRegion
{
public:
	ContentRegionInventory(size_t inventorySlots, size_t slotsPerRow);
	~ContentRegionInventory();


	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

private:
	Inventoryslot* mInventoryslots;
	size_t mSlotsNr;
};