#include "item.h"

#include "consumable.h"
#include "equipment.h"

game::items::Item::Item() noexcept
{
}

game::items::Item::~Item() noexcept
{
}

void game::items::Item::SetName()
{
}

void game::items::Item::SetDescription()
{
}

void game::items::Item::SetIType() {

}

void game::items::Item::Use(Hero& h)
{

}

std::vector<game::items::Item*> game::items::GetSavedItems() {
	// TODO add more items, update item classes
	std::vector<game::items::Item*>encounterableItems;

	// add consumables to encounterableItems
	auto consumables = GetConsumables();
	for (auto c : consumables) {
		encounterableItems.push_back(c);
	}

	// add equipment to encounterableItems
	//encounterableItems.push_back(new game::items::Shield(1));
	auto equipments = GetEquipments();
	for (auto e : equipments) {
		encounterableItems.push_back(e);
	}

	for (auto i : encounterableItems)
	{
		i->SetName();
		i->SetDescription();
		i->SetIType();
	}

	return encounterableItems;
}