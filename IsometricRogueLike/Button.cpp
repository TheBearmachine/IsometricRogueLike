#include "Button.h"
#include "ResourceManager.h"
#include "EventManager.h"
#include "Constants.h"
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
	mSize = sf::Vector2f((float)mSprite.getTextureRect().width, (float)mSprite.getLocalBounds().height);
}

Button::~Button()
{

}

void Button::setSpriteTexture(std::string texName)
{
	mSprite.setTexture(ResourceManager::getInstance().getTexture(texName));
	mSize = sf::Vector2f((float)mSprite.getTextureRect().left, (float)mSprite.getLocalBounds().top);
	adjustTextPosition();
}

void Button::setTextString(const std::string &text)
{
	mText.setString(text);
	adjustTextPosition();
}

void Button::setTextFont(const std::string & font)
{
	mText.setFont(ResourceManager::getInstance().getFont(font));
	adjustTextPosition();
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
	mSprite.setFrame(2);
}

void Button::onReleaseInside()
{
	if (mListener)
		mListener->buttonAction(mClickAction);
	if (mMouseInside)
		mSprite.setFrame(1);
	else
		mSprite.setFrame(0);
}

void Button::setActive(bool active)
{
	mIsActive = active;

	if (active)
		mSprite.setFrame(0);
	else
		mSprite.setFrame(3);
}

sf::FloatRect Button::getSpriteBounds() const
{
	return mSprite.getGlobalBounds();
}

void Button::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mSprite, states);
	target.draw(mText, states);
}

void Button::adjustTextPosition()
{
	float x = (mSprite.getLocalBounds().width - mText.getLocalBounds().width) / 2.0f;
	float y = (mSprite.getLocalBounds().height - mText.getLocalBounds().height) / 2.0f;
	mText.setPosition(x, y);
}
