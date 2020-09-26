#include "ActionGotoTile.h"
#include "ActionHelper.h"
#include "VectorFunctions.h"
#include "Movement.h"
#include "Entity.h"
#include "Map.h"
#include "Tile.h"

ActionGotoTile::ActionGotoTile() :
    Action(GotoTile)
{
    addPrecondition(ActionHelper::Conditions::DontGotoTile);
    addEffect(ActionHelper::Conditions::DoGotoTile);
}

ActionGotoTile::~ActionGotoTile()
{
}

bool ActionGotoTile::isDone()
{
    return mDone;
}

bool ActionGotoTile::requiresinRange()
{
    return true;
}

bool ActionGotoTile::checkProceduralPrecondition(Entity * agent)
{
    return (mTargetTile);
}

bool ActionGotoTile::perform(Entity * self, const sf::Time & deltaTime)
{
    mDone = true;
    mTargetTile = nullptr;
    Action::doReset();
    return true;
}

bool ActionGotoTile::planPath(Entity * self)
{
    bool pathExists = false;
    if (!mTargetTile) return false;
    std::stack<TileNode*> path;
    auto mc = self->getMovementComponent();
    auto cm = getCurrentMap();
    auto start = cm->getTileIndexFromCoords(mc->getCurrentTarget());
    auto end = cm->getTileIndexFromCoords(mTargetTile->getPosition());
    pathExists = (getCurrentMap()->findPath(start, end, path) == 1);
    setTargetEntity(self);

    mc->setPath(path);
    return pathExists;
}

bool ActionGotoTile::getInRange(Entity * self) const
{
    if (!mTargetTile) return false;
    float dist = VectorFunctions::vectorMagnitudeSquared(self->getPosition() - mTargetTile->getPosition());

    // Should be a small float, smaller than the height of a tile
    return  dist <= 10.0f;
}

void ActionGotoTile::doReset()
{
    mDone = false;

}

void ActionGotoTile::setTargetTile(Tile * tile)
{
    mTargetTile = tile;
}
