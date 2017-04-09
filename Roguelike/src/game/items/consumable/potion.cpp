#include "potion.h"

game::items::consumable::Potion::Potion() noexcept
{
}

game::items::consumable::Potion::~Potion() noexcept
{
}

void game::items::consumable::Potion::SetName()
{
	name = "Potion";
}

void game::items::consumable::Potion::SetDescription()
{
	description = "A spray-type medicine for treating wounds. It can be used to restore 10 HP to an injured hero.";
}

void game::items::consumable::Potion::Use(Hero* h)
{
	// increase hero health some way
	h->Heal(10);
	amount--;
}
