#include "Window.h"
#include "ResourceManager.h"
#include "DrawingManager.h"
#include "WindowManager.h"
#include "Tooltip.h"
#include "Constants.h"
#include <SFML/Graphics/RenderTarget.hpp>

static const float TOP_THICKNESS = 30.0f;
static const float BORDER_THICKNESS = 2.0f;
static const float CONTENT_INDENTATION = 4.0f;

static const std::string CLOSE_BUTTON_TEX = Constants::Filepaths::ImagesFolder + "CrossIcon.png";

static const sf::Vector2f DEFAULT_WINDOW_SIZE(300.0f, 200.0f);
static const std::string DOTS = "...";

static sf::RenderTarget* mRenderTarget;
static WindowManager* mWIndowManager;
static Tooltip* mTooptipPointer = nullptr;

Window::Window() :
	Window("Window", sf::Vector2f(), DEFAULT_WINDOW_SIZE)
{
}

Window::Window(const std::string &windowName, const sf::Vector2f & position, const sf::Vector2f & size) :
	mWIndowNameString(windowName),
	mWindowName(windowName, ResourceManager::getInstance().getFont(Constants::Filepaths::DefaultFont), (unsigned)(TOP_THICKNESS - (2.0f * BORDER_THICKNESS))),
	mBorder(size), mTop(sf::Vector2f(size.x, TOP_THICKNESS)),
	mTopDragable(this, sf::Vector2f(size.x, TOP_THICKNESS), 0),
	mCloseButton(this, CLOSE_BUTTON_TEX, 0), mVisible(true)
{
	setPosition(position);
	setStaticDrawPosition(true);
	mContentOffset.move(BORDER_THICKNESS * (CONTENT_INDENTATION * .5f),
						TOP_THICKNESS + BORDER_THICKNESS * (CONTENT_INDENTATION * .5f));
	mContentOffset.setParentTransform(this);

	mTopDragable.setParentTransform(this);
	mBorder.setOutlineThickness(-BORDER_THICKNESS);
	mBorder.setOutlineColor(Constants::Game::WindowBorderColor);
	mBorder.setFillColor(Constants::Game::WindowFillColor);

	mTop.setOutlineThickness(-BORDER_THICKNESS);
	mTop.setOutlineColor(Constants::Game::WindowTopBorderColor);
	mTop.setFillColor(Constants::Game::WindowTopFillColor);

	mWindowName.setPosition(BORDER_THICKNESS * BORDER_THICKNESS, BORDER_THICKNESS);
	mWindowName.setFillColor(sf::Color::White);

	float iconWidth = mCloseButton.getSize().x;
	mCloseButton.setParentTransform(this);
	mCloseButton.setTextString("");
	mCloseButton.setPosition(size.x - iconWidth, 0.0f);
	mCloseButton.setTooltipText("Close window.");

	setSize(size);

    // Shorten strings that are too long
	restructureText();
}

Window::~Window()
{
	unregisterEvents();
	clearContentRegions();
}

bool Window::createWindow(Window ** outWin, const std::string & windowName, const sf::Vector2f & position, const sf::Vector2f & size)
{
	if (!mWIndowManager) return false;
	Window* win = new  Window(windowName, position, size);
	*outWin = win;
	mWIndowManager->addWindow(win);

	return true;
}

void Window::registerEvents()
{
	Clickable::registerEvents();
}

void Window::unregisterEvents()
{
	Clickable::unregisterEvents();
	resetState();
}

bool Window::observe(const sf::Event & _event)
{
	bool retVal = Clickable::observe(_event);

	if( mCloseButton.observe(_event)) return true;
	if (mTopDragable.observe(_event)) return true;

	for (auto cr : mContentRegions)
		cr->delegateEvent(_event);

	return retVal;
}

void Window::onClickInside(const sf::Event& button)
{
	mWIndowManager->arrangeWindows(this);
}

void Window::onMouseOver(bool mouseOver)
{
	if (mTooptipPointer)
		mTooptipPointer->doDrawTooltip(false);
}

void Window::addContentRegion(ContentRegion* contentRegion)
{
	mContentRegions.push_back(contentRegion);
	contentRegion->setParentTransform(&mContentOffset);
}

void Window::clearContentRegions()
{
	while (!mContentRegions.empty())
	{
		delete mContentRegions.back();
		mContentRegions.pop_back();
	}
}

void Window::setVisibility(bool visible)
{
	mVisible = visible;
	if (visible)
		mWIndowManager->arrangeWindows(this);
	else
	{
		mCloseButton.resetState();
		if (mMouseInside && mTooptipPointer)
			mTooptipPointer->doDrawTooltip(false);
		resetState();
	}
}

bool Window::getVisible() const
{
	return mVisible;
}

void Window::setWindowSize(const sf::Vector2f & size)
{
	mBorder.setSize(size);
	mTop.setSize(sf::Vector2f(size.x, TOP_THICKNESS));
	mTopDragable.setSize(sf::Vector2f(size.x, TOP_THICKNESS));
	setSize(size);
	restructureText();
	fitWindow();
}

void Window::setWindowContentSize(const sf::Vector2f & size)
{
	sf::Vector2f newSize = size;
	newSize.x += BORDER_THICKNESS * CONTENT_INDENTATION;
	newSize.y += mTop.getSize().y + BORDER_THICKNESS * CONTENT_INDENTATION;

	mBorder.setSize(newSize);
	mTop.setSize(sf::Vector2f(newSize.x, TOP_THICKNESS));
	mTopDragable.setSize(sf::Vector2f(newSize.x, TOP_THICKNESS));
	setSize(newSize);
	restructureText();
	fitWindow();
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

void Window::setWindowListener(IWindowListener * windowListener)
{
	mWindowListener = windowListener;
}

void Window::resetState()
{
	Clickable::resetState();
	mTopDragable.resetState();
	mCloseButton.resetState();
	for (auto cr : mContentRegions)
	{
		cr->resetState();
	}
}

void Window::setup(sf::RenderTarget * window)
{
	mRenderTarget = window;
}

void Window::setWindowManager(WindowManager * winMan)
{
	mWIndowManager = winMan;
}

void Window::setTooltipPointer(Tooltip * tooltipPointer)
{
	mTooptipPointer = tooltipPointer;
}

void Window::onDrag(const sf::Vector2f & mouseDelta, const sf::Vector2f & mousePos, const sf::Event& button)
{
	//if (button.mouseButton.button == sf::Mouse::Left)
	//{
	move(mouseDelta);
	fitWindow();
	//}
}

void Window::drawPrep(DrawingManager * drawingMan)
{
	drawingMan->addDrawable(this);
}

void Window::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (!mVisible) return;

	states.transform *= getTransform();
	target.draw(mBorder, states);
	target.draw(mTop, states);
	target.draw(mWindowName, states);
	target.draw(mCloseButton, states);

	for (size_t i = 0; i < mContentRegions.size(); i++)
		target.draw(*mContentRegions[i], states);
}

void Window::onClose()
{
	if (mWindowListener)
	{
		resetState();
		mWindowListener->onWindowClose(this);
	}
}

void Window::restructureText()
{
	float iconWidth = mCloseButton.getSize().x;
	float topWidth = mTop.getSize().x - BORDER_THICKNESS * 3.0f - iconWidth;
	mWindowName.setString(mWIndowNameString);
	if (topWidth < 50.0f)
	{
		mWindowName.setString("");
		return;
	}
	if (mWindowName.getGlobalBounds().width > topWidth)
	{
		sf::Text dots(DOTS, ResourceManager::getInstance().getFont(Constants::Filepaths::DefaultFont));
		while ((mWindowName.getGlobalBounds().width + dots.getGlobalBounds().width) > topWidth)
		{
			std::string newString = mWindowName.getString();
			newString.pop_back();
			mWindowName.setString(newString);
		}
		mWindowName.setString(mWindowName.getString() + dots.getString());
	}
	mCloseButton.setPosition(mTop.getSize().x - iconWidth, 0.0f);
}

void Window::fitWindow()
{
	// Limit movement to inside the render window
	if (!mRenderTarget) return;
	const sf::Vector2f &pos = getPosition();
	const sf::Vector2f &winSize = getWindowSize();
	const sf::Vector2f renderWinSize(mRenderTarget->getDefaultView().getSize());

	if (pos.x < 0.0f)
		setPosition(0.0f, pos.y);
	else if (pos.x + winSize.x > renderWinSize.x)
		setPosition(renderWinSize.x - winSize.x, pos.y);

	if (pos.y < 0.0f)
		setPosition(pos.x, 0.0f);
	else if (pos.y + winSize.y > renderWinSize.y)
		setPosition(pos.x, renderWinSize.y - winSize.y);
}

void Window::buttonAction(unsigned int action)
{
	switch (action)
	{
	case 0:
		// Close window
		onClose();
		break;

	default:
		break;
	}
}
