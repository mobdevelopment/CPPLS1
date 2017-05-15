#include "consumable.h"

#include "consumable\potion.h"
#include "consumable\rarecandy.h"

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

void game::items::Consumable::ImAConsumable()
{
}

std::vector<game::items::Consumable*> game::items::GetConsumables()
{
	std::vector<game::items::Consumable*>consumableItems;

	consumableItems.push_back(new items::consumable::Potion(1));
	consumableItems.push_back(new items::consumable::RareCandy(1));

	return consumableItems;
}
