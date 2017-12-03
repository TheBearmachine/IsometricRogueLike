#pragma once
#include "Clickable.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Drawable.hpp>

__interface IInventoryslotListener
{
	void buttonAction(unsigned int ID);
	void onHover(/*Should contain some parameter (item type in the item slot?)*/);
};

class Inventoryslot : public Clickable, public sf::Drawable
{
public:
	Inventoryslot();
	Inventoryslot(size_t ID);
	virtual ~Inventoryslot();

	void setListener(IInventoryslotListener* listener);
	void setID(size_t ID);

	sf::Vector2f getSize() const;

	virtual void observe(const sf::Event & _event) override;
	virtual void onMouseOver(bool mouseOver) override;
	virtual void onClickInside() override;
	virtual void onReleaseInside() override;

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

private:
	sf::Sprite mSprite;
	size_t mID;
	IInventoryslotListener* mListener;
};