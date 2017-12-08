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

	virtual void registerEvents();
	virtual void unregisterEvents();

	void setRegionSize(const sf::Vector2f &size);
	sf::Vector2f getRegionSize() const;
	sf::Vector2f getRegionUsableSize() const;

	virtual void drawPrep(DrawingManager* drawingMan);
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;


private:
	sf::RectangleShape mRegionBG;

};