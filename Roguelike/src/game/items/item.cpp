#include "item.h"
#include "potion.h"
#include "shield.h"
#include "weapon.h"

game::items::Item::Item() noexcept
{
}

game::items::Item::~Item() noexcept
{
}

game::items::Item::Item(int a) noexcept
{
	amount = a;
}

void game::items::Item::SetName()
{
}

void game::items::Item::SetEffect()
{
}

void game::items::Item::Use(Hero* h)
{
}

std::vector<game::items::Item*> game::items::GetSavedItems() {
	// TODO add more items, update item classes
	std::vector<game::items::Item*>encounterableItems; 
	encounterableItems.push_back(new game::items::Potion(1));
	encounterableItems.push_back(new game::items::Shield(1));

	for (auto i : encounterableItems)
	{
		i->SetName();
		i->SetEffect();
	}
	return encounterableItems;
}