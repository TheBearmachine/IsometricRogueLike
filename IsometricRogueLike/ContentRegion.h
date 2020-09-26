#pragma once
#include "Button.h"
#include "DrawThis.h"
#include <vector>
#include <SFML/Graphics/RectangleShape.hpp>

class ContentRegion :public DrawThis, public Transformabetter
{
public:
	ContentRegion();
	ContentRegion(const sf::Vector2f &size);
	~ContentRegion();

	virtual bool delegateEvent(const sf::Event &_event);

	virtual void setRegionSize(const sf::Vector2f &size);
	sf::Vector2f getRegionSize() const;
	sf::Vector2f getRegionUsableSize() const;

	virtual void drawPrep(DrawingManager* drawingMan);
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

	virtual void resetState();

private:
	sf::RectangleShape mRegionBG;

};