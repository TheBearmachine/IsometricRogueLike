#include "ItemDatabase.h"
#include <fstream>
#include <sstream>
#include <string>

static const char* DB_FILE = "Resources/ItemDatabase/ItemDatabase.txt";
//struct ItemTypes
//{
//	ItemTypes(size_t iD, std::string itemTypeName) :
//		ID(iD), ItemTypeName(itemTypeName)
//	{}
//	size_t ID;
//	std::string ItemTypeName;
//};
//static const ItemTypes ItemTypesList[]{
//	ItemTypes(1, "Sword"),
//	ItemTypes(2, "Axe"),
//	ItemTypes(3, "Mace"),
//	ItemTypes(4, "Staff"),
//
//	ItemTypes(5, "Cloth"),
//	ItemTypes(6, "Leather"),
//	ItemTypes(7, "Chainmail"),
//	ItemTypes(8, "Plate"),
//
//	ItemTypes(9, "Consumable"),
//
//};

//An item can have more than one type (Ex. Sword | Mace)
const enum ItemTypeList
{
	Sword		= 0b00000001,
	Axe			= 0b00000010,
	Mace		= 0b00000100,
	Staff		= 0b00001000,

	Cloth		= 0b00010000,
	Leather		= 0b00100000,
	Chainmail	= 0b01000000,
	Plate		= 0b10000000,

	Consumable	= 500,

};


//struct EquipmentSlot
//{
//	EquipmentSlot(size_t iD, std::string equipmentSlotName) :
//		ID(iD), EquipmentSlotName(equipmentSlotName)
//	{}
//	size_t ID;
//	std::string EquipmentSlotName;
//};
//static const EquipmentSlot EquipmentSlotNames[]{
//	EquipmentSlot(1,"NonEquippable"),
//	EquipmentSlot(2,"Helmet"),
//	EquipmentSlot(3,"Chest"),
//	EquipmentSlot(4,"Legs"),
//	EquipmentSlot(5, "ChestAndLegs"),
//	EquipmentSlot(6,"Mainhand"),
//	EquipmentSlot(7,"Offhand"),
//	EquipmentSlot(8,"Twohand"),
//	EquipmentSlot(9,"Finger"),
//	EquipmentSlot(10,"Neck")
//};	

const enum EquipmentSlotList
{
	NonEquippable,
	Helmet,
	Chest,
	Legs,
	ChestAndLegs,
	Mainhand,
	Offhand,
	Twohand,
	Finger,
	Neck,
};

ItemDatabase::ItemDatabase()
{
	std::ifstream ifs(DB_FILE);
	std::istringstream iss;
	std::string line, name;
	size_t ID;

	// The first line is a template, so read and discard
	std::getline(ifs, line);

	while (std::getline(ifs, line))
	{
		iss.clear();
		iss.str(line);

		ItemContents ic;

		iss >> ID >> ic.eqSlot >> ic.iType;
		for (size_t i = 0; i < Item::NrProperties; i++)
		{
			iss >> ic.prop[i];
		}
		iss >> ic.value >> ic.texFile;
		char flush;
		iss.read(&flush, 1);

		std::getline(iss, line);
		size_t cur = 0;
		bool done = false;
		while (!done)
		{
			cur = line.find('|', cur + 1);
			if (cur == std::string::npos)
				done = true;
			else if (line[cur + 1] == 'e' && line[cur + 2] == '|')
			{
				// Found a endsequence
				ic.name = line.substr(0, cur);
				ic.desc = line.substr(cur + 3);

				done = true;
			}
		}

		mItemDatabase[ID] = ic;
	}
}

ItemDatabase & ItemDatabase::getInstance()
{
	static ItemDatabase idb;
	return idb;
}

ItemDatabase::~ItemDatabase()
{

}

const ItemDatabase::ItemContents ItemDatabase::getItem(size_t ID) const
{
	const ItemContents &temp = mItemDatabase.at(ID);
	Item item;
	item.setItemTyp((Item::ItemTypes)temp.iType);
	item.setEquipmentSlot((Item::EquipmentSlot)temp.eqSlot);
	item.setItemName(temp.name);
	item.setItemDescription(temp.desc);
	item.setItemTex(temp.texFile);
	for (size_t i = 0; i < Item::NrProperties; i++)
		item.setProperty(temp.prop[i], i);

	return mItemDatabase.at(ID);
}
