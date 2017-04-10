#include "talisman.h"

game::items::consumable::Talisman::Talisman() noexcept
{
}

game::items::consumable::Talisman::~Talisman() noexcept
{
}

void game::items::consumable::Talisman::SetName()
{
	name = "Talisman";
}

void game::items::consumable::Talisman::SetDescription()
{
	description = "A nutritious drink. It raises the Defense chance of the hero by 2%.";
}

void game::items::consumable::Talisman::SetIType()
{
	iType = "Consumable";
}

void game::items::consumable::Talisman::Use(Hero& h)
{
	h.DefUp(2);
	amount--;
}