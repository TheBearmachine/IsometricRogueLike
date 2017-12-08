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

__interface IWindowListener
{
	void onWindowClose(Window* window);
};

class Window : public IDragListener, public IButtonListener, public Transformabetter, public DrawThis
{
public:
	Window();
	Window(const std::string &windowName, const sf::Vector2f &position, const sf::Vector2f &size);
	~Window();

	void registerEvents();
	void unregisterEvents();

	void addContentRegion(ContentRegion* contentRegion);
	void clearContentRegions();
	void setVisibility(bool visible);

	void setWindowSize(const sf::Vector2f &size);
	void setWindowContentSize(const sf::Vector2f &size);
	sf::Vector2f getContentSize() const;
	sf::Vector2f getWindowSize() const;

	void setWindowListener(IWindowListener* windowListener);

	static void setup(sf::RenderTarget* window);
	virtual void onDrag(const sf::Vector2f &mouseDelta, const sf::Vector2f &mousePos) override;
	virtual void buttonAction(unsigned int action) override;

	virtual void drawPrep(DrawingManager* drawingMan);
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

private:
	void onClose();
	void restructureText();

	IWindowListener* mWindowListener;

	Dragable mTopDragable;
	sf::RectangleShape mBorder;
	sf::RectangleShape mTop;
	sf::Text mWindowName;
	std::string mWIndowNameString;
	std::vector<ContentRegion*> mContentRegions;
	Button mCloseButton;
	bool mVisible;
};