#include "ItemDatabase.h"
#include <fstream>
#include <sstream>
#include <string>

static const char* DB_FILE = "Resources/ItemDatabase/ItemDatabase.txt";
static const std::string ItemTypesNames[]{
	"Sword",
	"Axe",
	"Mace",
	"Staff",

	"Cloth",
	"Leather",
	"Chainmail",
	"Plate",

	"Consumable"

};

static const std::string EquipmenSlotNames[]{
	"NonEquippable",
	"Helmet",
	"Chest",
	"Legs",
	"ChestAndLegs",
	"Mainhand",
	"Offhand",
	"Twohand",
	"Finger",
	"Neck"
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

		std::getline(iss, line);
		size_t cur = 0;
		bool done = false;
		while (!done)
		{
			cur = line.find('|', cur + 1);
			if (line.size() > cur + 2)
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
