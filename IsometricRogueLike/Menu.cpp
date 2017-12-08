#include "Menu.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include "DrawingManager.h"
#include "Constants.h"
#include "Button.h"

static const float BORDER_THICKNESS = 2.0f;

Menu::Menu(const sf::Vector2f &size) :
	mBackground(size)
{
	setStaticDrawPosition(true);
	mBackground.setOutlineThickness(-BORDER_THICKNESS);
	mBackground.setFillColor(Constants::Game::WindowFillColor);
	mBackground.setOutlineColor(Constants::Game::WindowBorderColor);
}

Menu::~Menu()
{
	clearButtons();
}

void Menu::addButton(Button * button)
{
	mButtons.push_back(button);
	button->setParentTransform(this);
	button->setStaticDrawPosition(true);
}

void Menu::clearButtons()
{
	while (!mButtons.empty())
	{
		delete mButtons.back();
		mButtons.pop_back();
	}
}

void Menu::setBackgroundSize(const sf::Vector2f & size)
{
	mBackground.setSize(size);
}

sf::Vector2f Menu::getBackgroundSize() const
{
	return mBackground.getSize();
}

void Menu::registerEvents()
{
	for (auto b : mButtons)
	{
		b->registerEvents();
	}
}

void Menu::unregisterEvents()
{
	for (auto b : mButtons)
	{
		b->unregisterEvents();
	}
}

void Menu::drawPrep(DrawingManager * drawingMan)
{
	drawingMan->addDrawable(this);
}

void Menu::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform = getGlobalTransform();
	target.draw(mBackground, states);

	for (auto b : mButtons)
		target.draw(*b, states);
}
