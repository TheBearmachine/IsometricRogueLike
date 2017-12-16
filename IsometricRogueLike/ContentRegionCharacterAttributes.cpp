#include "ContentRegionCharacterAttributes.h"
#include "ResourceManager.h"
#include "Constants.h"
#include <SFML/Graphics/RenderTarget.hpp>

static const std::string ATTRIBUTE_NAMES[]{ "Lvl", "Str", "Per", "End", "Mem", "Cha", "Wis " };
static const std::string OTHER_NAMES[]{ "Attack", "Defence", "Sight" };

static const int CHAR_SIZE = 15;

ContentRegionCharacterAttributes::ContentRegionCharacterAttributes() :
	ContentRegion()
{
	sf::Font* font = &ResourceManager::getInstance().getFont(Constants::Filepaths::DefaultFont);
	for (size_t i = 0; i < STATNR; i++)
	{
		mTextAttributes[i].setFont(*font);
		mTextAttributes[i].setCharacterSize(CHAR_SIZE);
		mTextAttributes[i].setFillColor(sf::Color::White);
		mTextAttributes[i].setPosition(sf::Vector2f(5.0f, 125.0f + 20.0f * i));
		mTextAttributes[i].setString(ATTRIBUTE_NAMES[i] + ": " + std::to_string(i + 2));
	}
	for (size_t i = 0; i < OTHERNR; i++)
	{
		mTextOther[i].setFont(*font);
		mTextOther[i].setCharacterSize(CHAR_SIZE);
		mTextOther[i].setFillColor(sf::Color::White);
		mTextOther[i].setPosition(sf::Vector2f(5.0f + 150.0f, 125.0f + 20.0f * i));
		mTextOther[i].setString(OTHER_NAMES[i] + ": " + std::to_string(i + 2));
	}

	setRegionSize(sf::Vector2f(410.0f, 320.0f));
}

ContentRegionCharacterAttributes::~ContentRegionCharacterAttributes()
{

}

void ContentRegionCharacterAttributes::registerEvents()
{

}

void ContentRegionCharacterAttributes::unregisterEvents()
{

}

void ContentRegionCharacterAttributes::drawPrep(DrawingManager * drawingMan)
{

}

void ContentRegionCharacterAttributes::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	ContentRegion::draw(target, states);

	states.transform = getGlobalTransform();
	for (int i = 0; i < STATNR; i++)
	{
		target.draw(mTextAttributes[i], states);
	}
	for (int i = 0; i < OTHERNR; i++)
	{
		target.draw(mTextOther[i], states);
	}
}
