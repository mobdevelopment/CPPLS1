#include "potion.h"

game::items::Potion::Potion() noexcept
{
}

game::items::Potion::~Potion() noexcept
{
}

void game::items::Potion::SetName()
{
	name = "Potion";
}

void game::items::Potion::SetEffect()
{
	effect = "Heals the players health by 10 hp";
}

void game::items::Potion::Use(Hero* h)
{
	// increase hero health some way
	h->Heal(10);
}
