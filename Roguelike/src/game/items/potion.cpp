#include "potion.h"

game::items::Potion::Potion() noexcept
{
}

game::items::Potion::~Potion() noexcept
{
}

void game::items::Potion::Use(Hero* h)
{
	// increase hero health some way
	h->Heal(10);
}
