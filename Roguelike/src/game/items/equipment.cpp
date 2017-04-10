#include "equipment.h"

#include "equipment/weapon.h"
#include "equipment/shield.h"

game::items::Equipment::Equipment() noexcept
{
}

game::items::Equipment::~Equipment() noexcept
{
}

void game::items::Equipment::ImAEquipable()
{
}

std::vector<game::items::Equipment*> game::items::GetEquipments()
{
	std::vector<game::items::Equipment*> equipableItems;
	// add Weapons to equipableItems
	//auto weapons = GetWeapons();
	auto weapons = game::items::equipment::GetWeapons();
	for (auto w : weapons) {
		equipableItems.push_back(w);
	}

	// add Shields to equipableItems
	auto shields = game::items::equipment::GetShields();
	for (auto s : shields) {
		equipableItems.push_back(s);
	}

	return equipableItems;
}