#include "ContentRegionMenu.h"
#include "ResourceManager.h"
#include <SFML/Graphics/RenderTarget.hpp>



ContentRegionMenu::ContentRegionMenu(IButtonListener* buttonListener, Orientation orientation, size_t buttonsPerRow) :
	mButtonListener(buttonListener),
	mOrientation(orientation),
	mButtonsPerRow(buttonsPerRow),
	mCurentButtonNr(0)
{
}

ContentRegionMenu::~ContentRegionMenu()
{
}

void ContentRegionMenu::addButton(const std::string &text, size_t action)
{
	mButtons.push_back(Button());
	Button& b = mButtons.back();
	b.setParentTransform(this);
	b.setTextString(text);
	b.setListener(mButtonListener);
	sf::Vector2f pos, size(ResourceManager::getInstance().getTexture("").getSize());
	switch (mOrientation)
	{
	case ContentRegionMenu::Horizontal:
		//pos.x = ;
		break;

	case ContentRegionMenu::Vertical:

		break;

	default:
		break;
	}
}

void ContentRegionMenu::clearButtons()
{
	mButtons.clear();
}

bool ContentRegionMenu::delegateEvent(const sf::Event & _event)
{
	for (auto b : mButtons)
	{
		b.observe(_event);
	}
	return false;
}

void ContentRegionMenu::drawPrep(DrawingManager * drawingMan)
{
}

void ContentRegionMenu::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	ContentRegion::draw(target, states);

	states.transform = getGlobalTransform();
	for (auto b : mButtons)
	{
		target.draw(b, states);
	}
}
