#pragma once
#include "EnhancedText.h"
#include "Clickable.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

__interface ITextBoxScrollListener
{
	virtual void onScroll(const sf::Event & button) = 0;
};

class TextBox : public DrawThis, public Clickable
{
public:
	TextBox();
	TextBox(const std::string &string, const sf::Vector2f size);
	~TextBox();

	void setConfines(const sf::Vector2f& size);
	void setString(const std::string &string);
	void setFont(const std::string &string);
	void setFontSize(size_t size);
	sf::Vector2f getBounds() const;

	void setTextPosition(const sf::Vector2f& pos);
	//Accepts values between 0.0 and 1.0
	void setTextRelativePosition(const sf::Vector2f& pos);
	const sf::Vector2f& getTextPosition() const;
	const sf::Vector2f getTextRelativePosition() const;

	void setScrollListener(ITextBoxScrollListener* listener);

	virtual void drawPrep(DrawingManager* drawingMan);
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

	virtual void onScrollInside(const sf::Event& button) override;

private:
	void updateTexture();
	void fitText();

	ITextBoxScrollListener* mListener;

	sf::RenderTexture mBuffer;
	EnhancedText mTextObj;
	sf::RectangleShape mToDraw;
};
