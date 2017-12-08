#include "Button.h"
#include "ResourceManager.h"
#include "EventManager.h"
#include "Constants.h"
#include "DrawingManager.h"
#include <SFML/Graphics/RenderWindow.hpp>

static const std::string DEFAULT_TEXTURE = Constants::Filepaths::ImagesFolder + "Button.png";

Button::Button() :
	Button(nullptr, DEFAULT_TEXTURE, 0U)
{

}

Button::Button(IButtonListener * listener, const std::string &textureName, size_t action) :
	mText("Button", ResourceManager::getInstance().getFont(Constants::Filepaths::DefaultFont), 26),
	mIsActive(true), mListener(listener), mClickAction(action)
{
	AnimationSetup animSetup = AnimationSetup::DefaultButtonSetup();
	animSetup.textureName = textureName;
	mSprite.setup(animSetup);
	mSize = mSprite.getSize();
	mSprite.setParentTransform(this);
}

Button::~Button()
{

}

void Button::setSpriteTexture(const std::string &texName)
{
	mSprite.setSpriteTexture(texName);
	mSize = mSprite.getSize();
	adjustTextPosition();
}

void Button::setTextString(const std::string &text)
{
	mText.setString(text);
	adjustTextPosition();
}

void Button::setTextSize(size_t size)
{
	mText.setCharacterSize(size);
	adjustTextPosition();
}

void Button::setTextFont(const std::string & font)
{
	mText.setFont(ResourceManager::getInstance().getFont(font));
	adjustTextPosition();
}

sf::Vector2f Button::getSize() const
{
	return mSprite.getSize();
}

void Button::setListener(IButtonListener * listener)
{
	mListener = listener;
}

void Button::setAction(size_t action)
{
	mClickAction = action;
}

void Button::onMouseOver(bool mouseOver)
{
	if (mIsActive)
	{
		if (mouseOver)
			mSprite.setFrame(1);
		else
			mSprite.setFrame(0);
	}
}

void Button::onClickInside()
{
	if (mIsActive)
		mSprite.setFrame(2);
}

void Button::onReleaseInside()
{
	if (mIsActive)
	{
		if (mListener)
			mListener->buttonAction(mClickAction);
		if (mMouseInside)
			mSprite.setFrame(1);
		else
			mSprite.setFrame(0);
	}
}

void Button::setActive(bool active)
{
	mIsActive = active;

	if (active)
	{
		registerEvents();
		mSprite.setFrame(0);
	}
	else
	{
		unregisterEvents();
		mSprite.setFrame(3);
	}
}

void Button::drawPrep(DrawingManager * drawingMan)
{
	drawingMan->addDrawable(this);
}

void Button::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform = getGlobalTransform();
	target.draw(mSprite, states);
	target.draw(mText, states);
}

void Button::adjustTextPosition()
{
	float x = (mSprite.getSize().x - mText.getLocalBounds().width) / 2.0f;
	float y = (mSprite.getSize().y - mText.getLocalBounds().height) / 2.0f;
	mText.setPosition(x, y);
}
