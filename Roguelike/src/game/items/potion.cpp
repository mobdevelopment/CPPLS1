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
	effect = "A spray-type medicine for treating wounds. It can be used to restore 10 HP to an injured hero.";
}

void game::items::Potion::Use(Hero* h)
{
	// increase hero health some way
	h->Heal(10);
	amount--;
}
