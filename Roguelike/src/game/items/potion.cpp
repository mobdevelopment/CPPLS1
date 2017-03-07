#include "potion.h"

game::items::Potion::Potion() noexcept
{
}

game::items::Potion::~Potion() noexcept
{
}

void game::items::Potion::Use()
{
	// increase hero health some way

	delete this;
}
