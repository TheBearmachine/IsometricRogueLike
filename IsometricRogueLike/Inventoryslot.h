#pragma once
#include "Clickable.h"
#include <SFML/Graphics/Sprite.hpp>
#include "DrawThis.h"

__interface IInventoryslotListener
{
	void buttonAction(unsigned int ID);
	void onHover(/*Should contain some parameter (item type in the item slot?)*/);
};

class Inventoryslot : public Clickable, public DrawThis
{
public:
	Inventoryslot();
	Inventoryslot(size_t ID);
	virtual ~Inventoryslot();

	void setListener(IInventoryslotListener* listener);
	void setID(size_t ID);

	sf::Vector2f getSize() const;

	virtual bool observe(const sf::Event & _event) override;
	virtual void onMouseOver(bool mouseOver) override;
	virtual void onClickInside() override;
	virtual void onReleaseInside() override;
	virtual void onDragInside(const sf::Vector2f &mouseDelta, const sf::Vector2f &mousePos);

	virtual void drawPrep(DrawingManager* drawingMan);
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

private:
	sf::Sprite mSprite;
	size_t mID;
	IInventoryslotListener* mListener;
};