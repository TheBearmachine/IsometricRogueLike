#include "ContentRegionInventory.h"
#include <SFML/Graphics/RenderTarget.hpp>

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
	sf::Vector2f regionSize = getRegionUsableSize();
	sf::Vector2f slotSize = mInventoryslots->getSize();
	size_t nrColumns = (size_t)std::ceil((float)inventorySlots / (float)slotsPerRow);
	sf::Vector2f contentSize((float)slotsPerRow * (slotSize.x + PADDING), (float)nrColumns * (slotSize.x + PADDING));
	setRegionSize(contentSize);

	for (size_t i = 0; i < inventorySlots; i++)
	{
		float xPos = float(i % slotsPerRow) * (slotSize.x + PADDING);
		float yPos = float(i / slotsPerRow) * (slotSize.x + PADDING);
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

void ContentRegionInventory::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	ContentRegion::draw(target, states);
	states.transform *= getTransform();
	for (size_t i = 0; i < mSlotsNr; i++)
	{
		target.draw(mInventoryslots[i], states);
	}
}
