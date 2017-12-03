#pragma once
#include "Button.h"
#include <vector>
#include <SFML/Graphics/RectangleShape.hpp>

class ContentRegion :public sf::Drawable, public Transformabetter
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
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;


private:
	sf::RectangleShape mRegionBG;

};