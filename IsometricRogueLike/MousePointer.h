#pragma once
#include "EventObserver.h"
#include "Transformabetter.h"
#include "Animation.h"
#include "DrawThis.h"
#include <string>

class Item;
namespace sf
{
	class RenderWindow;
}

class MousePointer : public DrawThis, public Transformabetter
{
public:
	MousePointer();
	~MousePointer();

	void setSprite(const std::string &textureName);

	Item* switchItem(Item* newItem);
	Item* getItem();

	void update(const sf::Time &deltaTime);

	virtual void drawPrep(DrawingManager* drawingMan) override;
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

	static void setup(sf::RenderWindow* window);

private:
	Animation mSprite;
	Item* mItem;
};