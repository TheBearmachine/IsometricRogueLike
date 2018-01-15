#include "EnhancedText.h"
#include "ResourceManager.h"
#include "DrawingManager.h"
#include "Constants.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <sstream>

static const std::string DEFAULT_FONT = Constants::Filepaths::DefaultFont;

EnhancedText::EnhancedText() :
	EnhancedText("", DEFAULT_FONT, sf::Vector2f())
{

}

EnhancedText::EnhancedText(const std::string & string, const std::string &font, const sf::Vector2f& confines) :
	mString(string), mConfines(confines)
{
	mFont = &ResourceManager::getInstance().getFont(font);
	setStaticDrawPosition(true);

#ifdef DEBUG_MODE
	mDebugConfines.setOutlineColor(sf::Color::Red);
	mDebugConfines.setFillColor(sf::Color::Transparent);
	mDebugConfines.setOutlineThickness(1.0f);
#endif // DEBUG_MODE

	parseString();
}

EnhancedText::~EnhancedText()
{

}

void EnhancedText::setSize(size_t size)
{
	mSize = size;
	mNeedsUpdate = true;
}

void EnhancedText::setConfines(const sf::Vector2f & size)
{
	mConfines = size;
#ifdef DEBUG_MODE
	mDebugConfines.setSize(mConfines);
#endif // DEBUG_MODE
	mNeedsUpdate = true;
}

void EnhancedText::setString(const std::string & string)
{
	mString = string;
	parseString();
	mNeedsUpdate = true;
}

void EnhancedText::setFont(const std::string & string)
{
	mFont = &ResourceManager::getInstance().getFont(string);
	mNeedsUpdate = true;
}

void EnhancedText::drawPrep(DrawingManager * drawingMan)
{
	drawingMan->addDrawable(this);
}

void EnhancedText::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (!mFont) return;
	if (mNeedsUpdate) updateVertexArray();

	const sf::Texture& tex = mFont->getTexture(mSize);
	states.texture = &tex;
	states.transform = getGlobalTransform();

	target.draw(mVertices, states);

#ifdef DEBUG_MODE
	//target.draw(mDebugConfines, states);
#endif // DEBUG_MODE

}

void EnhancedText::parseString()
{
	std::stringstream ss(mString);

	char parseChar = 0;
	sf::Uint8 r = 0xff, g = 0xff, b = 0xff;
	char colChar[2];
	mActualCaracters = 0;

	mTextInfo.clear();

	while (true)
	{
		parseChar = ss.get();
		if (ss.eof()) break;

		if (parseChar == '|')
		{
			parseChar = ss.get();
			if (ss.eof()) break;

			// Color code (|cxxxxxx|) where x is a hexadecimal number
			if (parseChar == 'c')
			{
				colChar[0] = ss.get();
				colChar[1] = ss.get();
				if (ss.eof()) break;
				r = std::stoi(std::string(colChar), 0, 16);

				colChar[0] = ss.get();
				colChar[1] = ss.get();
				if (ss.eof()) break;
				g = std::stoi(std::string(colChar), 0, 16);

				colChar[0] = ss.get();
				colChar[1] = ss.get();
				if (ss.eof()) break;
				b = std::stoi(std::string(colChar), 0, 16);

				parseChar = ss.get();
				if (ss.eof()) break;

				if (parseChar != '|')
				{
					printf("Error: Faulty format on enhanced text!\n");
				}
			}
			// Room for other codes
			else {}
		}
		else
		{
			mTextInfo.push_back(EnhancedTextStruct());
			// Delimiting character (likely only works on windows)
			if (parseChar != '\n')
				mActualCaracters++;

			EnhancedTextStruct &ets = mTextInfo.back();
			ets.character = parseChar;
			ets.color = sf::Color(r, g, b);
		}
	}
}

void EnhancedText::updateVertexArray() const
{
	mNeedsUpdate = false;
	if (!mFont)
	{
		printf("Warning: No font set up for enhanced text!\n");
		return;
	}

	sf::Vector2f currentPos;
	size_t count = 0;
	mVertices.resize(mActualCaracters * 4);
	float  lineSpacing = mFont->getLineSpacing(mSize);
	mVertices.setPrimitiveType(sf::PrimitiveType::Quads);
	for (size_t i = 0; i < mTextInfo.size(); i++)
	{
		char currentChar = mTextInfo[i].character;
		if (currentChar != '\n')
		{
			sf::Glyph glyph = mFont->getGlyph(currentChar, mSize, false);

			sf::IntRect UV = glyph.textureRect;
			sf::FloatRect bounds = glyph.bounds;

			sf::Vertex* quad = &mVertices[count * 4];
			quad[0].position = sf::Vector2f(currentPos.x, currentPos.y + (lineSpacing - bounds.height));
			quad[1].position = sf::Vector2f(currentPos.x + bounds.width, currentPos.y + (lineSpacing - bounds.height));
			quad[2].position = sf::Vector2f(currentPos.x + bounds.width, currentPos.y + lineSpacing);
			quad[3].position = sf::Vector2f(currentPos.x, currentPos.y + lineSpacing);

			quad[0].texCoords = sf::Vector2f((float)UV.left, (float)UV.top);
			quad[1].texCoords = sf::Vector2f((float)(UV.left + UV.width), (float)UV.top);
			quad[2].texCoords = sf::Vector2f((float)(UV.left + UV.width), (float)(UV.top + UV.height));
			quad[3].texCoords = sf::Vector2f((float)UV.left, (float)(UV.top + UV.height));

			quad[0].color = mTextInfo[i].color;
			quad[1].color = mTextInfo[i].color;
			quad[2].color = mTextInfo[i].color;
			quad[3].color = mTextInfo[i].color;

			if (i < mTextInfo.size() - 1)
			{
				char nextChar = mTextInfo[i + 1].character;
				/*if (nextChar == '\n')
				{
					i++;
					currentPos.x = 0.0f;
					currentPos.y += lineSpacing;
				}*/
				// Check to see if the word exceed the defined width confine
				if (nextChar == ' ' || nextChar == '\n' || i + 2 == mTextInfo.size())
				{
					currentPos.x += glyph.advance + mFont->getKerning(currentChar, nextChar, mSize);

					size_t wordLength = 0;
					float wordWidth = 0.0f;
					float rightBound = currentPos.x;
					if (currentPos.x > mConfines.x)
					{
						while (true)
						{
							if (i - wordLength - 1U == ~0U) break;
							if (mTextInfo[i - wordLength - 1U].character == ' ' ||
								mTextInfo[i - wordLength - 1U].character == '\n') break;

							wordLength++;
						}
						// Need to querry the width of the word to avoid infinite
						// loopage here on words that are longer than the confines
						wordWidth = rightBound - mVertices[(count - wordLength) * 4].position.x;
						if (i - wordLength - 1U != ~0U || wordWidth < mConfines.x)
						{
							currentPos.x = 0.0f;
							currentPos.y += lineSpacing;
							count -= wordLength + 1;
							i -= wordLength + 1;
						}
					}
				}
				else
				{
					currentPos.x += glyph.advance + mFont->getKerning(mTextInfo[i].character, mTextInfo[i + 1].character, mSize);
				}
			}
			count++;
		}
	}
}
