#include "weapon.h"

#include "weapon\ironsword.h"

game::items::equipment::Weapon::Weapon() noexcept
{
}

game::items::equipment::Weapon::~Weapon() noexcept
{
}

void game::items::equipment::Weapon::SetName()
{
	name = "";
}

void game::items::equipment::Weapon::SetDescription()
{
	description = "";

}

void game::items::equipment::Weapon::Equip(Hero * h)
{
	//amount--;
}

void game::items::equipment::Weapon::UnEquip(Hero* h) {

}

std::vector<game::items::equipment::Weapon*> game::items::equipment::GetWeapons()
{
	std::vector<game::items::equipment::Weapon*>equipableWeapons;

	equipableWeapons.push_back(new game::items::equipment::weapon::IronSword());

	return equipableWeapons;
}