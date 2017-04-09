#include "grenade.h"

game::items::consumable::Grenade::Grenade() noexcept
{
}

game::items::consumable::Grenade::~Grenade() noexcept
{
	
}

void game::items::consumable::Grenade::Use()
{
	// destroy multiple rooms but keep graph algorithm in mind

	delete this;
}
