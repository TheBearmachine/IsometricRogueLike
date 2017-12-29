#pragma once
#include "ContentRegion.h"
#include "Button.h"
#include <vector>

class ContentRegionMenu : public ContentRegion
{
public:
	enum Orientation
	{
		Horizontal,
		Vertical
	};

	ContentRegionMenu(IButtonListener* buttonListener, Orientation orientation = Vertical, size_t buttonsPerRow = 3);
	~ContentRegionMenu();

	void addButton(const std::string &text, size_t action);
	void clearButtons();

	virtual bool delegateEvent(const sf::Event &_event) override;

	virtual void drawPrep(DrawingManager* drawingMan) override;
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

private:
	std::vector<Button> mButtons;
	IButtonListener* mButtonListener;
	Orientation mOrientation;
	size_t mButtonsPerRow;
	size_t mCurentButtonNr;
};