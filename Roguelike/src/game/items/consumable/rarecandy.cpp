#include "rarecandy.h"

game::items::consumable::RareCandy::RareCandy() noexcept
{
}

game::items::consumable::RareCandy::~RareCandy() noexcept
{
}

void game::items::consumable::RareCandy::SetName()
{
	name = "RareCandy";
}

void game::items::consumable::RareCandy::SetDescription()
{
	description = "A candy that is packed with energy. When consumed, it will instantly raise the level of the hero by one.";
}

void game::items::consumable::RareCandy::Use(Hero* h)
{
	h->RareCandy();
	amount--;
}
