#include "weapon.h"

game::items::Weapon::Weapon() noexcept
{
}

game::items::Weapon::~Weapon() noexcept
{
}

void game::items::Weapon::SetName()
{
	name = "";
}

void game::items::Weapon::SetEffect()
{
	effect = "";

}

void game::items::Weapon::Use(Hero * h)
{
	amount--;
}