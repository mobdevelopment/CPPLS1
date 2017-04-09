#include "ironsword.h"

game::items::equipment::weapon::IronSword::IronSword() noexcept
{
}

game::items::equipment::weapon::IronSword::~IronSword() noexcept
{
}

void game::items::equipment::weapon::IronSword::SetName()
{
	name = "IronSword";
}

void game::items::equipment::weapon::IronSword::SetDescription()
{
	description = "A simple Iron Sword which boosts the hero's strength with 2.";
}

void game::items::equipment::weapon::IronSword::Equip(Hero * h)
{
}

void game::items::equipment::weapon::IronSword::UnEquip(Hero * h)
{
}
