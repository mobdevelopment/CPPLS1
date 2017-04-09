#include "talisman.h"

game::items::Talisman::Talisman() noexcept
{
}

game::items::Talisman::~Talisman() noexcept
{
}

void game::items::Talisman::SetName()
{
	name = "Talisman";
}

void game::items::Talisman::SetEffect()
{
	effect = "A nutritious drink. It raises the Defense chance of the hero by 2%.";
	
}

void game::items::Talisman::Use(Hero * h)
{
	h->DefUp(2);
	amount--;
}