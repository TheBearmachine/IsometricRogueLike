#pragma once
#include "Clickable.h"
#include "Animation.h"
#include "Transformabetter.h"
#include "DrawThis.h"
#include <string>
#include <vector>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Text.hpp>

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

	void setListener(IButtonListener* listener);
	void setAction(size_t action);

	virtual void onMouseOver(bool mouseOver) override;
	virtual void onClickInside() override;
	virtual void onReleaseInside() override;

	virtual void setActive(bool active);

	virtual void drawPrep(DrawingManager* drawingMan);
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

private:
	void adjustTextPosition();

	size_t mClickAction;
	IButtonListener* mListener;
	Animation mSprite;
	sf::Text mText;

	bool mIsActive;
};
