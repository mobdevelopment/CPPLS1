#include "grenade.h"

game::items::consumable::Grenade::Grenade() noexcept
{
}

game::items::consumable::Grenade::~Grenade() noexcept
{
	
}

void game::items::consumable::Grenade::SetIType()
{
	iType = "Consumable";
}

void game::items::consumable::Grenade::Use(Hero* h)
{
	// destroy multiple rooms but keep graph algorithm in mind

	delete this;
}
