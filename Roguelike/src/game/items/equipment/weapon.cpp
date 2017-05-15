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
}

void game::items::equipment::Weapon::SetDescription()
{
}

void game::items::equipment::Weapon::SetIType()
{
}

void game::items::equipment::Weapon::Use(Hero& h)
{
	//amount--;
}

int game::items::equipment::Weapon::GetEffect()
{
	return 0;
}

std::vector<game::items::equipment::Weapon*> game::items::equipment::GetWeapons()
{
	std::vector<game::items::equipment::Weapon*>equipableWeapons;

	equipableWeapons.push_back(new game::items::equipment::weapon::IronSword());

	return equipableWeapons;
}