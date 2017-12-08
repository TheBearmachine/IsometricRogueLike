#pragma once
#include <SFML/Graphics/Drawable.hpp>

class DrawingManager;

class DrawThis : public sf::Drawable
{
public:
	DrawThis() :mZBuffer(0), mStaticDrawPosition(false) {}
	~DrawThis() {}

	void setZBuffer(int val) { mZBuffer = val; }
	int getZBuffer() const { return mZBuffer; }

	void setStaticDrawPosition(bool staticPos) { mStaticDrawPosition = staticPos; }
	bool getStaticDrawPosition() const { return mStaticDrawPosition; }

	virtual void drawPrep(DrawingManager* drawingMan) = 0;
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const = 0;

private:
	int mZBuffer;
	bool mStaticDrawPosition;
};