#include "ItemManager.h"
#include "ItemDatabase.h"
#include "Inventory.h"
#include "Constants.h"
#include "Tile.h"
#include "MousePointer.h"

static MousePointer* mMousePointer;

ItemManager::ItemManager()
{

}

ItemManager::~ItemManager()
{
    while (!mItems.empty())
    {
        delete mItems.back();
        mItems.pop_back();
    }
}

void ItemManager::setMousePointer(MousePointer * mouseP)
{
    mMousePointer = mouseP;
}

Item * ItemManager::makeItem(size_t ID)
{
    ItemDatabase::ItemContents idb = ItemDatabase::getInstance().getItem(ID);
    Item *item = new Item();
    item->setItemTyp((Item::ItemTypes)idb.iType);
    item->setEquipmentSlot((Item::EquipmentSlot)idb.eqSlot);
    item->setItemName(idb.name);
    item->setItemDescription(idb.desc);
    item->setItemTex(Constants::Filepaths::ImagesFolder + "Items/" + idb.texFile + ".png");
    for (size_t i = 0; i < Item::NrProperties; i++)
        item->setProperty(idb.prop[i], i);

    mItems.push_back(item);

    return mItems.back();
}
