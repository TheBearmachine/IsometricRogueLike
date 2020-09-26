#pragma once
#include "DrawThis.h"
#include "Transformabetter.h"
#include <vector>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Font.hpp>

#ifdef DEBUG_MODE
#include <SFML/Graphics/RectangleShape.hpp>
#endif // DEBUG_MODE

// Text class that can be drawn with different colors for each character
class EnhancedText : public DrawThis, public Transformabetter
{
public:
	EnhancedText();
	EnhancedText(const std::string &string, const std::string &font, float maxWidth);
	~EnhancedText();

	void setFontSize(size_t size);
	void setConfines(float size);
	void setString(const std::string &string);
	void setFont(const std::string &string);
	sf::Vector2f getBounds() const;
	void forceUpdateVertexArray();

	virtual void drawPrep(DrawingManager* drawingMan);
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

private:
	struct EnhancedTextStruct
	{
		char character;
		sf::Color color;
	};

	void parseString();
	void updateVertexArray() const;
	void doUpdateVertexArray() const;

	float mMaxWidth;
	const sf::Font* mFont;
	std::string mString;
	size_t mActualCaracters;
	std::vector<EnhancedTextStruct> mTextInfo;
	mutable sf::VertexArray mVertices;
	mutable bool mNeedsUpdate;
	size_t mFontSize;

#ifdef DEBUG_MODE
	sf::RectangleShape mDebugConfines;
#endif // DEBUG_MODE


};
