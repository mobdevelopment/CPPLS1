#include "equipment.h"

#include "equipment/weapon.h"
#include "equipment/shield.h"

game::items::Equipment::Equipment() noexcept
{
}

game::items::Equipment::~Equipment() noexcept
{
}

void game::items::Equipment::SetName()
{
}

void game::items::Equipment::SetDescription()
{
}

void game::items::Equipment::SetIType() {

}

void game::items::Equipment::Use(Hero* h)
{
}

std::vector<game::items::Equipment*> game::items::GetEquipments()
{
	std::vector<game::items::Equipment*>equipableItems;
	// add Weapons to equipableItems
	//auto weapons = GetWeapons();
	auto weapons = equipment::GetWeapons();
	for (auto w : weapons) {
		equipableItems.push_back(w);
	}

	// add Shields to equipableItems
	auto shields = equipment::GetShields();
	for (auto s : shields) {
		equipableItems.push_back(s);
	}

	return equipableItems;
}