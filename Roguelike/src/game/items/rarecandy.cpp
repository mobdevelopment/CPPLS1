#include "rarecandy.h"

game::items::RareCandy::RareCandy() noexcept
{
}

game::items::RareCandy::~RareCandy() noexcept
{
}

void game::items::RareCandy::SetName()
{
	name = "RareCandy";
}

void game::items::RareCandy::SetEffect()
{
	effect = "	A candy that is packed with energy. When consumed, it will instantly raise the level of the hero by one.";
}

void game::items::RareCandy::Use(Hero* h)
{
	h->RareCandy();
	amount--;
}
