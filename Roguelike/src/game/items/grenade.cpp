#include "grenade.h"

game::items::Grenade::Grenade() noexcept
{
}

game::items::Grenade::~Grenade() noexcept
{
	
}

void game::items::Grenade::Use()
{
	// destroy multiple rooms but keep graph algorithm in mind

	delete this;
}
