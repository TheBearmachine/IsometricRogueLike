#pragma once
#include "Action.h"
#include <stack>

class Item;
class Tile;
class Inventory;
class ContentRegionInventory;
struct TileNode;

class ActionPickUpItem : public Action
{
public:
	ActionPickUpItem(Entity* owner, Item* item, Tile* fromTile, ContentRegionInventory* fromInv, Inventory* toInv);
	~ActionPickUpItem();

	bool isDone() override;
	bool inRange() override;
	bool checkProceduralPrecondition(Entity* agent) override;
	bool update(const sf::Time& deltaTime) override;

	const std::stack<TileNode*>& getPath() const;

private:
	Item* mItem;
	Entity* mOwner;
	Tile* mTargetTile;
	ContentRegionInventory* mFromInv;
	Inventory* mToInv;
	std::stack<TileNode*> mPath;

	bool mDone;
};
