#include "Tooltip.h"
#include "Constants.h"
#include "DrawingManager.h"
#include <SFML/System/Time.hpp>

static const float DEFAULT_WIDTH = 280.0f;
static const float DEFAULT_BORDER_WIDTH = 2.0f;
static const float DEFAULT_PADDING = 5.0f;
static const sf::Uint8 DEFAULT_ALPHA = 128;

static const float DEFAULT_TOOLTIP_DELAY = 1.0f;

static const sf::Color DEFAULT_BACKGROUND_COLOR = sf::Color(15, 15, 255, DEFAULT_ALPHA);
static const sf::Color DEFAULT_BACKGROUND_BORDER_COLOR = sf::Color(7, 7, 85, DEFAULT_ALPHA);


Tooltip::Tooltip() :
	Tooltip(DEFAULT_WIDTH, "Default Tooltip Text")
{

}

Tooltip::Tooltip(float width, const std::string& tooltipText) :
	mTooltipText(), mDoDraw(false)
{
	mTooltipText.setFontSize(20U);
	mTooltipText.setConfines(width);
	mTooltipText.setString(tooltipText);
	mTooltipText.setPosition(DEFAULT_PADDING, DEFAULT_PADDING); // Do something with anchoring?
	mTooltipText.setParentTransform(this);
	mTooltipDelay = mTooltipTimer = DEFAULT_TOOLTIP_DELAY;
}

Tooltip::~Tooltip()
{

}

void Tooltip::setTooltipText(const std::string & text)
{
	mTooltipText.setString(text);
	mTooltipText.forceUpdateVertexArray();
	sf::Vector2f size = mTooltipText.getBounds();
	//printf("Tooltip text size X: %f, Y: %f\n", size.x, size.y);
	size.x += DEFAULT_PADDING * 2;
	size.y += DEFAULT_PADDING * 2;
	mBackground.setSize(size);
	mBackground.setOutlineThickness(DEFAULT_BORDER_WIDTH);
	mBackground.setFillColor(DEFAULT_BACKGROUND_COLOR);
	mBackground.setOutlineColor(DEFAULT_BACKGROUND_BORDER_COLOR);
}

void Tooltip::doDrawTooltip(bool doDraw)
{
	mDoDraw = doDraw;
	if (!doDraw)
		mTooltipTimer = mTooltipDelay;
}

void Tooltip::setTooltipDelay(float timer)
{
	mTooltipDelay = mTooltipTimer = timer;
}

void Tooltip::update(const sf::Time & deltaTime)
{
	if (mDoDraw)
	{
		mTooltipTimer = std::max(mTooltipTimer - deltaTime.asSeconds(), 0.0f);
	}
}

void Tooltip::drawPrep(DrawingManager * drawingMan)
{
	drawingMan->addDrawable(this);
}

void Tooltip::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (!mDoDraw) return;
	if (mTooltipTimer > 0.0f) return;

	states.transform *= getTransform();
	target.draw(mBackground, states);
	target.draw(mTooltipText, states);
}
