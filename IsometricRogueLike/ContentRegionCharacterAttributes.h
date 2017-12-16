#pragma once
#include "ContentRegion.h"
#include <SFML/Graphics/Text.hpp>

class ContentRegionCharacterAttributes : public ContentRegion
{
public:
	ContentRegionCharacterAttributes();
	~ContentRegionCharacterAttributes();

	virtual void registerEvents() override;
	virtual void unregisterEvents() override;

	virtual void drawPrep(DrawingManager* drawingMan) override;
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;


private:
	static const int STATNR = 7;
	static const int OTHERNR = 3;

	sf::Text mTextAttributes[STATNR];
	sf::Text mTextOther[OTHERNR];
};
