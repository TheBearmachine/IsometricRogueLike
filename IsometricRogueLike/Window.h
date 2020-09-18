#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <vector>
#include "Button.h"
#include "Dragable.h"
#include "ContentRegion.h"
#include "Transformabetter.h"
#include "DrawThis.h"

class Window;
class WindowManager;
class Tooltip;

__interface IWindowListener
{
	void onWindowClose(Window* window);
};

class Window : public IDragListener, public IButtonListener, public Clickable, public DrawThis
{
private:
	Window();
	Window(const std::string &windowName, const sf::Vector2f &position, const sf::Vector2f &size);

public:
	~Window();

	static bool createWindow(Window** outWin, const std::string &windowName = "Window", const sf::Vector2f &position = sf::Vector2f(), const sf::Vector2f &size = sf::Vector2f());

	void registerEvents();
	void unregisterEvents();

	virtual bool observe(const sf::Event & _event) override;
	virtual void onClickInside(const sf::Event& button) override;
	virtual void onMouseOver(bool mouseOver) override;

	void addContentRegion(ContentRegion* contentRegion);
	void clearContentRegions();
	void setVisibility(bool visible);
	bool getVisible() const;

	void setWindowSize(const sf::Vector2f &size);
	void setWindowContentSize(const sf::Vector2f &size);
	sf::Vector2f getContentSize() const;
	sf::Vector2f getWindowSize() const;

	void setWindowListener(IWindowListener* windowListener);

	static void setup(sf::RenderTarget* window);
	static void setWindowManager(WindowManager* winMan);
	static void setTooltipPointer(Tooltip* tooltipPointer);
	virtual void onDrag(const sf::Vector2f &mouseDelta, const sf::Vector2f &mousePos, const sf::Event& button) override;
	virtual void buttonAction(unsigned int action) override;

	virtual void drawPrep(DrawingManager* drawingMan);
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

private:
	void onClose();
	void fitWindow();
	void restructureText();

	IWindowListener* mWindowListener;
	Transformabetter mContentOffset;

	Dragable mTopDragable;
	sf::RectangleShape mBorder;
	sf::RectangleShape mTop;
	sf::Text mWindowName;
	std::string mWIndowNameString;
	std::vector<ContentRegion*> mContentRegions;
	Button mCloseButton;
	bool mVisible;
};