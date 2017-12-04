#include "Window.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include "ResourceManager.h"
#include "Constants.h"

static const float TOP_THICKNESS = 30.0f;
static const float BORDER_THICKNESS = 2.0f;
static const float CONTENT_INDENTATION = 4.0f;

static const std::string CLOSE_BUTTON_TEX = Constants::Filepaths::ImagesFolder + "CrossIcon.png";

static const sf::Vector2f DEFAULT_WINDOW_SIZE(300.0f, 200.0f);
static const std::string DOTS = "...";

Window::Window() :
	Window("Window", sf::Vector2f(), DEFAULT_WINDOW_SIZE)
{

}

Window::Window(const std::string &windowName, const sf::Vector2f & position, const sf::Vector2f & size) :
	mWindowName(windowName, ResourceManager::getInstance().getFont(Constants::Filepaths::DefaultFont), (unsigned)(TOP_THICKNESS - (2.0f * BORDER_THICKNESS))),
	mBorder(size), mTop(sf::Vector2f(size.x, TOP_THICKNESS)),
	mDragable(this, sf::FloatRect(0.0f, 0.0f, size.x, TOP_THICKNESS)),
	mCloseButton(this, CLOSE_BUTTON_TEX, 0)
{
	setPosition(position);

	mDragable.setParentTransform(this);
	mBorder.setOutlineThickness(-BORDER_THICKNESS);
	mBorder.setOutlineColor(sf::Color(0, 0, 220));
	mBorder.setFillColor(sf::Color(0, 0, 170));

	mTop.setOutlineThickness(-BORDER_THICKNESS);
	mTop.setOutlineColor(sf::Color(0, 40, 200));
	mTop.setFillColor(sf::Color(0, 20, 170));

	mWindowName.setPosition(BORDER_THICKNESS * BORDER_THICKNESS, BORDER_THICKNESS);
	mWindowName.setFillColor(sf::Color::White);

	float iconWidth = mCloseButton.getSpriteBounds().width;
	mCloseButton.setPosition(size.x - iconWidth, 0.0f);
	mCloseButton.setTextString("");

	// Shorten strings that are too long
	if (mWindowName.getGlobalBounds().width > size.x - BORDER_THICKNESS * 3.0f)
	{
		sf::Text dots(DOTS, ResourceManager::getInstance().getFont(Constants::Filepaths::DefaultFont));
		while ((mWindowName.getGlobalBounds().width + dots.getGlobalBounds().width) > size.x - BORDER_THICKNESS * 3.0f)
		{
			std::string newString = mWindowName.getString();
			newString.pop_back();
			mWindowName.setString(newString);
		}
		mWindowName.setString(mWindowName.getString() + dots.getString());
	}
}

Window::~Window()
{
	clearContentRegions();
}

void Window::registerEvents()
{
	mDragable.registerEvents();
	for (auto cr : mContentRegions)
	{
		cr->registerEvents();
	}
}

void Window::unregisterEvents()
{
	mDragable.unregisterEvents();
	for (auto cr : mContentRegions)
	{
		cr->unregisterEvents();
	}
}

void Window::addContentRegion(ContentRegion* contentRegion)
{
	mContentRegions.push_back(contentRegion);
	contentRegion->setParentTransform(this);
	contentRegion->move(BORDER_THICKNESS * (CONTENT_INDENTATION * .5f),
						TOP_THICKNESS + BORDER_THICKNESS * (CONTENT_INDENTATION * .5f));
}

void Window::clearContentRegions()
{
	while (!mContentRegions.empty())
	{
		delete mContentRegions.back();
		mContentRegions.pop_back();
	}
}

void Window::setWindowSize(const sf::Vector2f & size)
{
	mBorder.setSize(size);
	mTop.setSize(sf::Vector2f(size.x, TOP_THICKNESS));
}

void Window::setWindowContentSize(const sf::Vector2f & size)
{
	sf::Vector2f newSize = size;
	newSize.x += BORDER_THICKNESS * CONTENT_INDENTATION;
	newSize.y += mTop.getSize().y + BORDER_THICKNESS * CONTENT_INDENTATION;

	mBorder.setSize(newSize);
	mTop.setSize(sf::Vector2f(newSize.x, TOP_THICKNESS));
}

sf::Vector2f Window::getContentSize() const
{
	sf::Vector2f size = mBorder.getSize();
	size.x -= BORDER_THICKNESS * CONTENT_INDENTATION;
	size.y -= mTop.getSize().y + BORDER_THICKNESS * CONTENT_INDENTATION;
	return size;
}

sf::Vector2f Window::getWindowSize() const
{
	return sf::Vector2f(mTop.getSize());
}

void Window::setup(EventManager * eventManager, sf::RenderTarget * window)
{
	mDragable.setup(eventManager, window);
}

void Window::onDrag(const sf::Vector2f & mouseDelta, const sf::Vector2f & mousePos)
{
	move(mouseDelta);
}

void Window::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mBorder, states);
	target.draw(mTop, states);
	target.draw(mWindowName, states);
	target.draw(mCloseButton, states);

	for (size_t i = 0; i < mContentRegions.size(); i++)
		target.draw(*mContentRegions[i], states);
}

void Window::buttonAction(unsigned int action)
{
	switch (action)
	{
	case 0:
		// Close window
		break;

	default:
		break;
	}
}
