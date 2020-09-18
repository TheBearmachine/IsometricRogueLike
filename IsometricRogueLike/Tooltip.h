#pragma once
#include "EnhancedText.h"
#include "DrawThis.h"
#include "Transformabetter.h"
#include <SFML/Graphics/RectangleShape.hpp>

namespace sf
{
	class Time;
}

class Tooltip : public DrawThis, public Transformabetter
{
public:
	Tooltip();
	Tooltip(float width, const std::string& tooltipText);
	~Tooltip();

	void setTooltipText(const std::string& text);
	void doDrawTooltip(bool doDraw);

	void setTooltipDelay(float timer);
	void update(const sf::Time &deltaTime);

	virtual void drawPrep(DrawingManager* drawingMan) override;
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

private:
	EnhancedText mTooltipText;
	sf::RectangleShape mBackground;

	float mTooltipDelay;
	float mTooltipTimer;
	bool mDoDraw;
};