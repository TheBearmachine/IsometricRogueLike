#include "EnhancedText.h"
#include "ResourceManager.h"
#include "DrawingManager.h"
#include "Constants.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <sstream>

static const std::string DEFAULT_FONT = Constants::Filepaths::DefaultFont;

EnhancedText::EnhancedText() :
	EnhancedText("", DEFAULT_FONT, 0)
{

}

EnhancedText::EnhancedText(const std::string & string, const std::string &font, float maxWidth) :
	mString(string), mMaxWidth(maxWidth)
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

void EnhancedText::setFontSize(size_t size)
{
	mFontSize = size;
	mNeedsUpdate = true;
}

void EnhancedText::setConfines(float size)
{
	mMaxWidth = size;
#ifdef DEBUG_MODE
	mDebugConfines.setSize({ mMaxWidth, 1.0f });
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

sf::Vector2f EnhancedText::getBounds() const
{
	sf::Vector2f v(mVertices.getBounds().left, mVertices.getBounds().top);
	return sf::Vector2f(mVertices.getBounds().left + mVertices.getBounds().width,
						mVertices.getBounds().top * 2.0f + mVertices.getBounds().height);
}

void EnhancedText::forceUpdateVertexArray()
{
	updateVertexArray();
}

void EnhancedText::drawPrep(DrawingManager * drawingMan)
{
	drawingMan->addDrawable(this);
}

void EnhancedText::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (!mFont) return;
	if (mNeedsUpdate) updateVertexArray();

	const sf::Texture& tex = mFont->getTexture(mFontSize);
	states.texture = &tex;
	states.transform = getGlobalTransform();

	target.draw(mVertices, states);

#ifdef DEBUG_MODE
	target.draw(mDebugConfines, states);
#endif // DEBUG_MODE

}

void EnhancedText::parseString()
{
	std::stringstream ss(mString);

	char parseChar = 0;
	sf::Uint8 r = 0xff, g = 0xff, b = 0xff;
	char colChar[2];
	mActualCaracters = 0;
	bool correctFormat = true;

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
					correctFormat = false;
				}
			}
			// Room for other codes
			else
			{
				correctFormat = false;
			}
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

	/*if(correctFormat)
		printf("Correct format on enhanced text\n");
	else
		printf("Error: Faulty format on enhanced text!\n");*/

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
	float  lineSpacing = mFont->getLineSpacing(mFontSize);
	mVertices.setPrimitiveType(sf::PrimitiveType::Quads);
	bool newWord = true;
	float newWordXPos;
	for (size_t i = 0; i < mTextInfo.size(); i++)
	{
		char currentChar = mTextInfo[i].character;
		if (currentChar != '\n')
		{
			sf::Glyph glyph = mFont->getGlyph(currentChar, mFontSize, false);

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

				// Check to see if the word exceed the defined width confine
				if (!newWord && (nextChar == ' ' || nextChar == '\n' || i + 2 == mTextInfo.size()))
				{
					currentPos.x += glyph.advance + mFont->getKerning(currentChar, nextChar, mFontSize);

					newWord = true;
					size_t wordLength = 0;
					float wordWidth = 0.0f;
					float rightBound = currentPos.x;
					if (currentPos.x > mMaxWidth)
					{
						while (true)
						{
							if (i - wordLength - 1U == ~(size_t)0) break;
							if (mTextInfo[i - wordLength - 1U].character == ' ' ||
								mTextInfo[i - wordLength - 1U].character == '\n') break;

							wordLength++;
						}

						// Need to querry the width of the word to avoid infinite
						// loopage on words that are wider than the confines
						wordWidth = rightBound - mVertices[(count - wordLength) * 4].position.x;
						if (i - wordLength - 1U != ~0U || wordWidth < mMaxWidth)
						{
							if (newWordXPos == 0.0f)
							{
								printf("Error: Word width %f exceeds max width %f!\n", wordWidth, mMaxWidth);
								return;
							}

							currentPos.x = 0.0f;
							currentPos.y += lineSpacing;
							count -= wordLength + 1;
							i -= wordLength + 1;
						}
					}
				}
				else
				{
					if (newWord)
					{
						newWord = false;
						newWordXPos = currentPos.x;
					}
					currentPos.x += glyph.advance + mFont->getKerning(mTextInfo[i].character, mTextInfo[i + 1].character, mFontSize);
				}
			}
			count++;
		}
		else
		{
			if (mTextInfo[i].character == '\n')
			{
				currentPos.x = 0.0f;
				currentPos.y += lineSpacing;
			}
		}
	}
}

void EnhancedText::doUpdateVertexArray() const
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
	float  lineSpacing = mFont->getLineSpacing(mFontSize);
	mVertices.setPrimitiveType(sf::PrimitiveType::Quads);
	bool newWord = true;
	float newWordXPos;
	for (size_t i = 0; i < mTextInfo.size(); i++)
	{
		char currentChar = mTextInfo[i].character;
		if (currentChar != '\n')
		{
			sf::Glyph glyph = mFont->getGlyph(currentChar, mFontSize, false);

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
				// Check to see if the word exceed the defined width confine
				if (!newWord && (nextChar == ' ' || nextChar == '\n' || i + 2 == mTextInfo.size()))
				{
					currentPos.x += glyph.advance + mFont->getKerning(currentChar, nextChar, mFontSize);

					newWord = true;
					size_t wordLength = 0;
					float wordWidth = 0.0f;
					float rightBound = currentPos.x;
					if (currentPos.x > mMaxWidth)
					{
						while (true)
						{
							if (i - wordLength - 1U == ~0U) break;
							if (mTextInfo[i - wordLength - 1U].character == ' ' ||
								mTextInfo[i - wordLength - 1U].character == '\n') break;

							wordLength++;
						}

						// Need to querry the width of the word to avoid infinite
						// loopage on words that are wider than the confines
						wordWidth = rightBound - mVertices[(count - wordLength) * 4].position.x;
						if (i - wordLength - 1U != ~0U || wordWidth < mMaxWidth)
						{
							if (newWordXPos == 0.0f)
							{
								printf("Error: Word width %f exceeds max width %f!\n", wordWidth, mMaxWidth);
								return;
							}

							currentPos.x = 0.0f;
							currentPos.y += lineSpacing;
							count -= wordLength + 1;
							i -= wordLength + 1;
						}
					}
				}
				else
				{
					if (newWord)
					{
						newWord = false;
						newWordXPos = currentPos.x;
					}
					currentPos.x += glyph.advance + mFont->getKerning(mTextInfo[i].character, mTextInfo[i + 1].character, mFontSize);
				}
			}
			count++;
		}
		else
		{
			if (mTextInfo[i].character == '\n')
			{
				currentPos.x = 0.0f;
				currentPos.y += lineSpacing;
			}
		}
	}
}
