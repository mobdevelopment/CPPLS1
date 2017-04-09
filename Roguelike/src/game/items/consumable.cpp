#include "consumable.h"

#include "consumable\potion.h"
#include "consumable\rarecandy.h"
#include "consumable\talisman.h"

game::items::Consumable::Consumable() noexcept
{
}

game::items::Consumable::~Consumable() noexcept
{
}

game::items::Consumable::Consumable(int a) noexcept
{
	amount = a;
}

void game::items::Consumable::SetName()
{
}

void game::items::Consumable::SetDescription()
{
}

void game::items::Consumable::Use(Hero* h)
{
}

std::vector<game::items::Consumable*> game::items::GetConsumables()
{
	std::vector<game::items::Consumable*>consumableItems;

	consumableItems.push_back(new game::items::consumable::Potion(1));
	consumableItems.push_back(new game::items::consumable::RareCandy(1));
	consumableItems.push_back(new game::items::consumable::Talisman(1));

	return consumableItems;
}
