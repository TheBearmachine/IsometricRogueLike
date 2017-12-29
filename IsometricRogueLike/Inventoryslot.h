#pragma once
#include "Clickable.h"
#include <SFML/Graphics/Sprite.hpp>
#include "DrawThis.h"

class Item;
class Inventoryslot;
class Inventory;
class Tile;

__interface IInventoryslotListener
{
	void buttonAction(Item* item, Inventoryslot* invSlot);
};

class Inventoryslot : public Clickable, public DrawThis
{
public:
	Inventoryslot();
	Inventoryslot(size_t ID);
	virtual ~Inventoryslot();

	static void setListener(IInventoryslotListener* listener);

	void setID(size_t ID);
	size_t getID() const;

	void setInventoryReference(Inventory* invRef);
	Inventory* getInventoryReference();

	void setTileReference(Tile* tileRef);
	Tile* getTileReference();

	void setItem(Item** item);
	Item** getItem();

	sf::Vector2f getSize() const;

	virtual void onMouseOver(bool mouseOver) override;
	virtual void onClickInside() override;
	virtual void onReleaseInside() override;
	virtual void onDragInside(const sf::Vector2f &mouseDelta, const sf::Vector2f &mousePos);

	virtual void drawPrep(DrawingManager* drawingMan);
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

private:
	sf::Sprite mSprite;
	Inventory* mInvRef;
	Tile* mTileRef;
	Item** mItem;
	size_t mID;
};