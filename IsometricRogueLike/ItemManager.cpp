#include "ItemManager.h"
#include "ItemDatabase.h"
#include "Inventory.h"
#include "Constants.h"
#include "MousePointer.h"

static MousePointer* mMousePointer;

ItemManager::ItemManager()
{

}

ItemManager::~ItemManager()
{

}

void ItemManager::setMousePointer(MousePointer * mouseP)
{
	mMousePointer = mouseP;
}

Item * ItemManager::makeItem(size_t ID)
{
	ItemDatabase::ItemContents temp = ItemDatabase::getInstance().getItem(ID);
	Item* item = new Item();
	item->setItemTyp((Item::ItemTypes)temp.iType);
	item->setEquipmentSlot((Item::EquipmentSlot)temp.eqSlot);
	item->setItemName(temp.name);
	item->setItemDescription(temp.desc);
	item->setItemTex(Constants::Filepaths::ImagesFolder + "Items/" + temp.texFile + ".png");
	for (size_t i = 0; i < Item::NrProperties; i++)
		item->setProperty(temp.prop[i], i);

	mItems.insert(item);

	return item;
}

void ItemManager::buttonAction(Item * item, Inventoryslot * invSlot)
{
	Item* temp = mMousePointer->getItem();
	temp = invSlot->getInventoryReference()->switchItemsInSlot(temp, invSlot->getID());
	mMousePointer->switchItem(temp);
}
