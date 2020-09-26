#include "ContentRegionMenu.h"
#include "ResourceManager.h"
#include "Constants.h"
#include <SFML/Graphics/RenderTarget.hpp>

const float PADDING = 2.0f;
static const std::string GUI_BUTTON = Constants::Filepaths::ImagesFolder + "GUIButton.png";

ContentRegionMenu::ContentRegionMenu(IButtonListener* buttonListener, Orientation orientation, size_t buttonsPerRow) :
	mButtonListener(buttonListener),
	mOrientation(orientation),
	mButtonsPerRow(buttonsPerRow)
{}

ContentRegionMenu::~ContentRegionMenu()
{
	clearButtons();
}

void ContentRegionMenu::addButton(const std::string &text, size_t action)
{
	Button* b = new Button(mButtonListener, GUI_BUTTON, action);
	b->setTextSize(12);
	mButtons.push_back(b);
	b->setParentTransform(this);
	b->setTextString(text);
	b->setListener(mButtonListener);
	sf::Vector2f pos, regSize, size(b->getSize());
	switch (mOrientation)
	{
	case ContentRegionMenu::Horizontal:
		pos.x = (float)(mButtons.size() - 1) * (size.x + PADDING) + PADDING;
		pos.y = PADDING;
		regSize.x = (float)mButtons.size() * (size.x + PADDING) + PADDING;
		regSize.y = size.y + PADDING * 2;
		break;

	case ContentRegionMenu::Vertical:
		pos.x = PADDING;
		pos.y = (float)(mButtons.size() - 1) *(size.y + PADDING) + PADDING;
		regSize.x = size.x + PADDING * 2;
		regSize.y = (float)mButtons.size() * (size.y + PADDING) + PADDING;
		break;

	default:
		break;
	}
	b->setPosition(pos);
	ContentRegion::setRegionSize(regSize);
}

void ContentRegionMenu::clearButtons()
{
	while (!mButtons.empty())
	{
		delete mButtons.back();
		mButtons.pop_back();
	}
}

bool ContentRegionMenu::delegateEvent(const sf::Event & _event)
{
	for (auto b : mButtons)
	{
		b->observe(_event);
	}
	return false;
}

void ContentRegionMenu::drawPrep(DrawingManager * drawingMan)
{}

void ContentRegionMenu::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	ContentRegion::draw(target, states);

	states.transform = getGlobalTransform();
	for (auto b : mButtons)
	{
		target.draw(*b, states);
	}
}
