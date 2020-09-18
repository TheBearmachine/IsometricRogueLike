#pragma once
#include "Clickable.h"
#include "AnimationTextureBased.h"
#include "Transformabetter.h"
#include "DrawThis.h"
#include <string>
#include <vector>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Text.hpp>

class Tooltip;

__interface IButtonListener
{
	void buttonAction(unsigned int action);
};

class Button : public Clickable, public DrawThis
{
public:
	Button();
	Button(IButtonListener *listener, const std::string &textureName, size_t action);
	virtual ~Button();

	void setSpriteTexture(const std::string &texName);
	void setTextString(const std::string &text);
	void setTextSize(size_t size);
	void setTextFont(const std::string &font);

	sf::Vector2f getSize() const;

	void setTooltipText(const std::string& text);
	static void setTooltipPointer(Tooltip* tooltipPointer);

	void setListener(IButtonListener* listener);
	void setAction(size_t action);

	virtual void onMouseOver(bool mouseOver) override;
	virtual void onClickInside(const sf::Event& button) override;
	virtual void onReleaseInside(const sf::Event& button) override;

	virtual void setActive(bool active);

	virtual void drawPrep(DrawingManager* drawingMan);
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

private:
	void adjustTextPosition();

	size_t mClickAction;
	IButtonListener* mListener;
	AnimationTextureBased mSprite;
	sf::Text mText;
	bool mDoDisplayTooltip;
	std::string mTooltipString;
	bool mIsActive;
};
