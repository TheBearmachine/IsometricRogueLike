#pragma once
#include "ContentRegion.h"
#include "Dragable.h"
#include "TextBox.h"

class ContentRegionTextBox : public ContentRegion,
	public IDragListener, public ITextBoxScrollListener
{
public:
	ContentRegionTextBox(const std::string& text, const sf::Vector2f& size);
	~ContentRegionTextBox();

	virtual void drawPrep(DrawingManager* drawingMan) override;
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

	virtual void setRegionSize(const sf::Vector2f &size) override;
	void setText(const std::string& text);

	virtual bool delegateEvent(const sf::Event &_event) override;

	virtual void resetState() override;

private:
	virtual void onDrag(const sf::Vector2f &mouseDelta, const sf::Vector2f &mousePos, const sf::Event& button) override;
	void onScroll(const sf::Event & button) override;
	void fitScroller();

	TextBox mTextBox;
	Clickable mMouseScrollArea;
	sf::RectangleShape mScrollerGraphics;
	Dragable mScroller;
};
