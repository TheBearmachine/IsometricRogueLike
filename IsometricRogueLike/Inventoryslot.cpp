#include "Inventoryslot.h"
#include "DrawingManager.h"
#include "ResourceManager.h"
#include "Item.h"
#include "Tooltip.h"
#include "Constants.h"
#include <SFML/Graphics/RenderTarget.hpp>

static const std::string TEXTURE_FILE = Constants::Filepaths::ImagesFolder + "Inventoryslot.png";

static IInventoryslotListener* mListener = nullptr;
static Tooltip* mTooptipPointer = nullptr;

Inventoryslot::Inventoryslot() :
    Inventoryslot(0U)
{
}

Inventoryslot::Inventoryslot(size_t ID) :
    mID(ID),
    mItem(nullptr),
    mInvRef(nullptr),
    mTileRef(nullptr),
    mSprite(ResourceManager::getInstance().getTexture(TEXTURE_FILE))
{
    mSize = sf::Vector2f((float)mSprite.getTextureRect().width, (float)mSprite.getTextureRect().height);
}

Inventoryslot::~Inventoryslot()
{
    unregisterEvents();
}

void Inventoryslot::setListener(IInventoryslotListener * listener)
{
    mListener = listener;
}

void Inventoryslot::setTooltipPointer(Tooltip * tooltipPointer)
{
    mTooptipPointer = tooltipPointer;
}

void Inventoryslot::setID(size_t ID)
{
    mID = ID;
}

size_t Inventoryslot::getID() const
{
    return mID;
}

void Inventoryslot::setInventoryReference(Inventory * invRef)
{
    mInvRef = invRef;
}

Inventory * Inventoryslot::getInventoryReference()
{
    return mInvRef;
}

void Inventoryslot::setTileReference(Tile * tileRef)
{
    mTileRef = tileRef;
}

Tile * Inventoryslot::getTileReference()
{
    return mTileRef;
}

void Inventoryslot::setItem(Item ** item)
{
    mItem = item;
}

Item ** Inventoryslot::getItem()
{
    return mItem;
}

sf::Vector2f Inventoryslot::getSize() const
{
    return mSize;
}


void Inventoryslot::onMouseOver(bool mouseOver)
{
    if (mouseOver)
    {
        if (mItem && *mItem)
        {
            std::string temp = (*mItem)->getItemName() + "\n\n"
                + (*mItem)->getItemDescription();
            mTooptipPointer->setTooltipText(temp);
            mTooptipPointer->doDrawTooltip(true);
        }
    }
    else
    {
        mTooptipPointer->doDrawTooltip(false);
    }
}

void Inventoryslot::onClickInside(const sf::Event& button)
{
    if (mListener && mItem)
        mListener->buttonAction(*mItem, this);
}

void Inventoryslot::onReleaseInside(const sf::Event& button)
{

}

void Inventoryslot::onDragInside(const sf::Vector2f & mouseDelta, const sf::Vector2f & mousePos)
{

}

void Inventoryslot::drawPrep(DrawingManager * drawingMan)
{
    drawingMan->addDrawable(this);
}

void Inventoryslot::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    states.transform = getGlobalTransform();
    target.draw(mSprite, states);

    if (mItem && *mItem != nullptr)
        (*mItem)->draw(target, states);
}
