#include "TextBox.h"
#include "DrawingManager.h"
#include "Constants.h"

TextBox::TextBox() :
    TextBox("Default text", sf::Vector2f(50.0f, 50.0f))
{}

TextBox::TextBox(const std::string & string, const sf::Vector2f size) :
    mTextObj(), mBuffer()
{
    mTextObj.setString(string);
    mTextObj.setFontSize(20U);
    setConfines(size);
}

TextBox::~TextBox()
{

}

void TextBox::setConfines(const sf::Vector2f & size)
{
    mBuffer.create((unsigned)size.x, (unsigned)size.y);
    mToDraw.setTexture(&mBuffer.getTexture(), true);
    mToDraw.setSize(size);
    mTextObj.setConfines(size.x);
    mTextObj.forceUpdateVertexArray();
    setSize(size);
    updateTexture();
}

void TextBox::setString(const std::string & string)
{
    mTextObj.setString(string);
    updateTexture();
}

void TextBox::setFont(const std::string & string)
{
    mTextObj.setFont(string);
    updateTexture();
}

void TextBox::setFontSize(size_t size)
{
    mTextObj.setFontSize(size);
    updateTexture();
}

sf::Vector2f TextBox::getBounds() const
{
    return sf::Vector2f(mBuffer.getSize());
}

void TextBox::setTextPosition(const sf::Vector2f & pos)
{
    mTextObj.setPosition(pos);
    updateTexture();
}

void TextBox::setTextRelativePosition(const sf::Vector2f & pos)
{
    float x = fmaxf(fminf(pos.x, 1.0f), 0.0f),
        y = fmaxf(fminf(pos.y, 1.0f), 0.0f);
    float xDiff = mTextObj.getBounds().x - mToDraw.getSize().x;
    float yDiff = mTextObj.getBounds().y - mToDraw.getSize().y;

    mTextObj.setPosition(-x * xDiff, -y * yDiff);
    updateTexture();
}

const sf::Vector2f & TextBox::getTextPosition() const
{
    return mTextObj.getPosition();
}

const sf::Vector2f TextBox::getTextRelativePosition() const
{
    sf::Vector2f rv = mTextObj.getPosition();
    float xDiff = mTextObj.getBounds().x - mToDraw.getSize().x;
    float yDiff = mTextObj.getBounds().y - mToDraw.getSize().y;

    rv.x = fabsf(rv.x / xDiff);
    rv.y = fabsf(rv.y / yDiff);

    return rv;
}

void TextBox::setScrollListener(ITextBoxScrollListener * listener)
{
    mListener = listener;
}

void TextBox::drawPrep(DrawingManager * drawingMan)
{}

void TextBox::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    states.transform = getGlobalTransform();
    target.draw(mToDraw, states);
}

void TextBox::onScrollInside(const sf::Event & button)
{
    if (mListener)
        mListener->onScroll(button);
}

void TextBox::updateTexture()
{
    fitText();
    mBuffer.clear(Constants::Game::ContentRegionFillColor);
    mBuffer.draw(mTextObj);
    mBuffer.display();
}

void TextBox::fitText()
{
    sf::Vector2f tV = mTextObj.getPosition();
    if (tV.x > 0.0f)
    {
        tV.x = 0.0f;
    }
    else if (tV.x < -mTextObj.getBounds().x)
    {
        tV.x = mTextObj.getBounds().x;
    }
    if (tV.y > 0.0f)
    {
        tV.y = 0.0f;
    }
    else if (tV.y < -mTextObj.getBounds().y + mToDraw.getSize().y)
    {
        tV.y = -mTextObj.getBounds().y + mToDraw.getSize().y;
    }
    mTextObj.setPosition(tV);
}
