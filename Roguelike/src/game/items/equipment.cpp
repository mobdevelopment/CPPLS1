#include "equipment.h"

#include "equipment/weapon.h"
#include "equipment/shield.h"
#include "equipment/bodyplate.h"
#include "equipment/legplate.h"
#include "equipment/shoes.h"

game::items::Equipment::Equipment() noexcept
{
}

game::items::Equipment::~Equipment() noexcept
{
}

int game::items::Equipment::GetEffect()
{
	return 0;
}

void game::items::Equipment::ImAEquipable()
{
}

std::vector<game::items::Equipment*> game::items::GetEquipments()
{
	std::vector<game::items::Equipment*> equipableItems;
	// add Weapons to equipableItems
	for (auto w : game::items::equipment::GetWeapons()) {
		equipableItems.push_back(w);
	}

	// add Shields to equipableItems
	for (auto s : game::items::equipment::GetShields()) {
		equipableItems.push_back(s);
	}

	// add Bodyplates to equipableItems
	for (auto b : game::items::equipment::GetBodyplates()) {
		equipableItems.push_back(b);
	}

	// add Legplates to equipableItems
	for (auto l : game::items::equipment::GetLegplates()) {
		equipableItems.push_back(l);
	}

	// add Shoes to equipableItems
	for (auto s : game::items::equipment::GetShoes()) {
		equipableItems.push_back(s);
	}

	return equipableItems;
}