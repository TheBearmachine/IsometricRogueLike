#pragma once
#include "EventObserver.h"
#include "Transformabetter.h"
#include "Animation.h"
#include "DrawThis.h"
#include <string>

class Item;

class MousePointer : public EventObserver, public DrawThis, public Transformabetter
{
public:
	MousePointer();
	~MousePointer();

	void setSprite(const std::string &textureName);

	Item* switchItem(Item* newItem);
	Item* getItem();

	virtual bool observe(const sf::Event& _event) override;

	virtual void drawPrep(DrawingManager* drawingMan) override;
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

	static void setup(sf::RenderTarget* window);

private:
	Animation mSprite;
	Item* mItem;
};