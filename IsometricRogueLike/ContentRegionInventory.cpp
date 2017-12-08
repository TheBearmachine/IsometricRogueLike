#include "ContentRegionInventory.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include "DrawingManager.h"

static const float PADDING = 2.0f;

ContentRegionInventory::ContentRegionInventory(size_t inventorySlots, size_t slotsPerRow) :
	ContentRegion(),
	mSlotsNr(inventorySlots)
{
	mInventoryslots = new Inventoryslot[inventorySlots];
	if (!mInventoryslots)
	{
		mSlotsNr = 0;
		return;
	}

	// Space out the slots evenly
	sf::Vector2f slotSize = mInventoryslots->getSize();
	size_t nrColumns = (size_t)std::ceil((float)inventorySlots / (float)slotsPerRow);
	sf::Vector2f contentSize((float)slotsPerRow * (slotSize.x + PADDING) + PADDING,
							 (float)nrColumns * (slotSize.x + PADDING) + PADDING);
	setRegionSize(contentSize);

	for (size_t i = 0; i < inventorySlots; i++)
	{
		float xPos = float(i % slotsPerRow) * (slotSize.x + PADDING) + PADDING;
		float yPos = float(i / slotsPerRow) * (slotSize.x + PADDING) + PADDING;
		mInventoryslots[i].setParentTransform(this);
		mInventoryslots[i].setID(i);
		mInventoryslots[i].setPosition(xPos, yPos);

		//mInventoryslots[i].setListener(); <-- Need to have a listener eventually
	}
}

ContentRegionInventory::~ContentRegionInventory()
{
	if (mSlotsNr != 0)
		delete[mSlotsNr] mInventoryslots;
}

void ContentRegionInventory::registerEvents()
{
	if (mSlotsNr != 0)
	{
		for (size_t i = 0; i < mSlotsNr; i++)
		{
			mInventoryslots[i].registerEvents();
		}
	}
}

void ContentRegionInventory::unregisterEvents()
{
	if (mSlotsNr != 0)
	{
		for (size_t i = 0; i < mSlotsNr; i++)
		{
			mInventoryslots[i].unregisterEvents();
		}
	}
}

void ContentRegionInventory::drawPrep(DrawingManager * drawingMan)
{

}

void ContentRegionInventory::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	ContentRegion::draw(target, states);

	states.transform = getGlobalTransform();
	for (size_t i = 0; i < mSlotsNr; i++)
		target.draw(mInventoryslots[i], states);
}
