#include "ironshield.h"

game::items::equipment::shield::IronShield::IronShield() noexcept
{
}

game::items::equipment::shield::IronShield::~IronShield() noexcept
{
}

void game::items::equipment::shield::IronShield::SetName()
{
	name = "IronSword";
}

void game::items::equipment::shield::IronShield::SetDescription()
{
	description = "A simple Iron Shield which boosts the hero's defence chance with 5%.";
}

void game::items::equipment::shield::IronShield::Equip(Hero * h)
{
}

void game::items::equipment::shield::IronShield::UnEquip(Hero * h)
{
}
