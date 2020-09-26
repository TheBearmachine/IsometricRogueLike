#pragma once
#include "Action.h"

class Tile;
class Inventory;
class ContentRegionInventory;
struct TileNode;

class ActionGotoTile : public Action
{
public:
    ActionGotoTile();
    ~ActionGotoTile();

    virtual bool isDone() override;
    virtual bool requiresinRange() override;
    bool checkProceduralPrecondition(Entity* agent) override;
    bool perform(Entity* self, const sf::Time& deltaTime) override;
    virtual bool planPath(Entity* self) override;
    virtual bool getInRange(Entity* self) const;
    virtual void doReset() override;

    void setTargetTile(Tile* tile);

private:
    Tile* mTargetTile;

    bool mDone;
};
