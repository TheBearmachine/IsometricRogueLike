#pragma once
#include "Action.h"

class Tile;
class Inventory;
class ContentRegionInventory;
struct TileNode;

class ActionPickUpItem : public Action
{
public:
	ActionPickUpItem();
	~ActionPickUpItem();

    virtual bool isDone() override;
    virtual bool requiresinRange() override;
	bool checkProceduralPrecondition(Entity* agent) override;
	bool perform(Entity* self, const sf::Time& deltaTime) override;
    virtual bool planPath(Entity* self) override;
    virtual bool getInRange(Entity* self) const;
    virtual void doReset() override;

    void setTargetTile(Tile* tile);
    void setFromInv(ContentRegionInventory* inv);

private:
	Tile* mTargetTile;
    ContentRegionInventory* mFromInv;

    bool mDone;
};
