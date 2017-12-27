#include "ContentRegionInventory.h"
#include "DrawingManager.h"
#include "Inventory.h"
#include <SFML/Graphics/RenderTarget.hpp>

static const float PADDING = 2.0f;

ContentRegionInventory::ContentRegionInventory(Inventory* refInv, size_t slotsPerRow) :
	ContentRegion(),
	mSlotsNr(0)
{
	mSlotsNr = refInv->getSize();
	mInventoryslots = new Inventoryslot[mSlotsNr];
	if (!mInventoryslots)
	{
		mSlotsNr = 0;
		return;
	}

	// Space out the slots evenly
	sf::Vector2f slotSize = mInventoryslots->getSize();
	size_t nrColumns = (size_t)std::ceil((float)mSlotsNr / (float)slotsPerRow);
	sf::Vector2f contentSize(
		(float)slotsPerRow * (slotSize.x + PADDING) + PADDING,
		(float)nrColumns * (slotSize.x + PADDING) + PADDING);
	setRegionSize(contentSize);

	for (size_t i = 0; i < mSlotsNr; i++)
	{
		float xPos = float(i % slotsPerRow) * (slotSize.x + PADDING) + PADDING;
		float yPos = float(i / slotsPerRow) * (slotSize.x + PADDING) + PADDING;
		mInventoryslots[i].setParentTransform(this);
		mInventoryslots[i].setID(i);
		mInventoryslots[i].setPosition(xPos, yPos);
		mInventoryslots[i].setItem(refInv->getItem(i));
		mInventoryslots[i].setInventoryReference(refInv);

		//mInventoryslots[i].setListener(); <-- Need to have a listener eventually
	}
}

ContentRegionInventory::~ContentRegionInventory()
{
	if (mSlotsNr != 0)
		delete[mSlotsNr] mInventoryslots;
}

Inventoryslot * ContentRegionInventory::getInventorySlot(size_t ID)
{
	return &mInventoryslots[ID];
}

void ContentRegionInventory::setInvSlotListener(IInventoryslotListener * listener)
{
	for (size_t i = 0; i < mSlotsNr; i++)
	{
		mInventoryslots[i].setListener(listener);
	}
}

bool ContentRegionInventory::delegateEvent(const sf::Event & _event)
{
	for (size_t i = 0; i < mSlotsNr; i++)
		mInventoryslots[i].observe(_event);

	return false;
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
