#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <vector>
#include "Button.h"
#include "Dragable.h"
#include "ContentRegion.h"
#include "Transformabetter.h"

class Window : public IDragListener, public Transformabetter, public sf::Drawable
{
public:
	Window();
	Window(const std::string &windowName, const sf::Vector2f &position, const sf::Vector2f &size);
	~Window();

	void registerEvents();
	void unregisterEvents();

	void addContentRegion(ContentRegion* contentRegion);
	void clearContentRegions();

	void setWindowSize(const sf::Vector2f &size);
	void setWindowContentSize(const sf::Vector2f &size);
	sf::Vector2f getContentSize() const;
	sf::Vector2f getWindowSize() const;

	void setup(EventManager* eventManager, sf::RenderTarget* window);
	virtual void onDrag(const sf::Vector2f &mouseDelta, const sf::Vector2f &mousePos) override;
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

private:
	Dragable mDragable;
	sf::RectangleShape mBorder;
	sf::RectangleShape mTop;
	sf::Text mWindowName;
	std::vector<ContentRegion*> mContentRegions;
};