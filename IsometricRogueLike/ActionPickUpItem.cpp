#include "ActionPickUpItem.h"
#include "VectorFunctions.h"
#include "Entity.h"
#include "Item.h"
#include "Map.h"
#include "Inventory.h"
#include "ContentRegionInventory.h"
#include "Tile.h"

ActionPickUpItem::ActionPickUpItem(Entity* owner, Item * item, Tile * fromTile, ContentRegionInventory* fromInv, Inventory * toInv) :
	mOwner(owner),
	mItem(item), mTargetTile(fromTile), mFromInv(fromInv), mToInv(toInv),
	mDone(false)
{
}

ActionPickUpItem::~ActionPickUpItem()
{
}

bool ActionPickUpItem::isDone()
{
	return mDone;
}

bool ActionPickUpItem::inRange()
{
	float dist = VectorFunctions::vectorMagnitudeSquared(mOwner->getPosition() - mTargetTile->getPosition());

	// Should be a small float, smaller than the height of a tile
	return  dist <= 10.0f;
}

bool ActionPickUpItem::checkProceduralPrecondition(Entity * agent)
{
	// Check if there is an available path
	while (!mPath.empty())
		mPath.pop();

	sf::Vector2i start = getCurrentMap()->getTileIndexFromCoords(mOwner->getPosition());
	sf::Vector2i end = getCurrentMap()->getTileIndexFromCoords(mTargetTile->getPosition());

	size_t result = getCurrentMap()->findPath(start, end, mPath);
	if (result != 1) return false;
	return true;
}

bool ActionPickUpItem::update(const sf::Time & deltaTime)
{
	if (mOwner->getInventory()->insertItem(mItem))
		mTargetTile->removeItem(mItem);
	else
	{

		return false;
	}
	size_t size = mTargetTile->getNrItems();
	mFromInv->createNewSlots(size, 4);
	for (size_t i = 0; i < size; i++)
	{
		mFromInv->getInventorySlot(i)->setItem(mTargetTile->getItem(i));
		mFromInv->getInventorySlot(i)->setTileReference(mTargetTile);
	}
	mDone = true;
	return true;
}

const std::stack<TileNode*>& ActionPickUpItem::getPath() const
{
	return mPath;
}
