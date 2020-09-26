#include "ActionPickUpItem.h"
#include "VectorFunctions.h"
#include "Entity.h"
#include "Movement.h"
#include "Item.h"
#include "Map.h"
#include "Inventory.h"
#include "ContentRegionInventory.h"
#include "Tile.h"
#include "ActionHelper.h"

ActionPickUpItem::ActionPickUpItem() :
    Action(PickUpItem), mTargetTile(nullptr), mDone(false)
{
    addPrecondition(ActionHelper::Conditions::DontFetchItem);
    addEffect(ActionHelper::Conditions::DoFetchItem);
}

ActionPickUpItem::~ActionPickUpItem()
{}

bool ActionPickUpItem::isDone()
{
    return mDone;
}

bool ActionPickUpItem::requiresinRange()
{
    return true;
}

bool ActionPickUpItem::getInRange(Entity* self) const
{
    if (!mTargetTile) return false;
    float dist = VectorFunctions::vectorMagnitudeSquared(self->getPosition() - mTargetTile->getPosition());

    // Should be a small float, smaller than the height of a tile
    return  dist <= 10.0f;
}

bool ActionPickUpItem::checkProceduralPrecondition(Entity * agent)
{
    // Check if there is an available path
    return  (getTargetItem() && mTargetTile);
}

bool ActionPickUpItem::perform(Entity* self, const sf::Time& deltaTime)
{
    Item* item = getTargetItem();
    if (!item) return false;
    if (self->getInventory()->insertItem(item))
    {
        mTargetTile->removeItem(item);
    }
    else
        return false;

    size_t size = mTargetTile->getNrItems();
    mFromInv->createNewSlots(size, 4);
    for (size_t i = 0; i < size; i++)
    {
        mFromInv->getInventorySlot(i)->setItem(mTargetTile->getItem(i));
        mFromInv->getInventorySlot(i)->setTileReference(mTargetTile);
    }

    mDone = true;
    mTargetTile = nullptr;
    Action::doReset();
    return true;
}

bool ActionPickUpItem::planPath(Entity* self)
{
    bool pathExists = false;
    if (!mTargetTile) return false;
    std::stack<TileNode*> path;
    auto mc = self->getMovementComponent();
    auto cm = getCurrentMap();
    auto start = cm->getTileIndexFromCoords(mc->getCurrentTarget());
    auto end = cm->getTileIndexFromCoords(mTargetTile->getPosition());
    pathExists = (getCurrentMap()->findPath(start, end, path) == 1);

    mc->setPath(path);
    return pathExists;
}

void ActionPickUpItem::doReset()
{
    //Action::doReset();
    mDone = false;
}

void ActionPickUpItem::setTargetTile(Tile * tile)
{
    mTargetTile = tile;
}

void ActionPickUpItem::setFromInv(ContentRegionInventory * inv)
{
    mFromInv = inv;
}
