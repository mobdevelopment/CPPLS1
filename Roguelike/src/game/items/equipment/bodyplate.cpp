#include "bodyplate.h"

#include "bodyplate/ironbodyplate.h"

game::items::equipment::Bodyplate::Bodyplate() noexcept
{
}

game::items::equipment::Bodyplate::~Bodyplate() noexcept
{
}

void game::items::equipment::Bodyplate::SetName()
{
}

void game::items::equipment::Bodyplate::SetDescription()
{
}

void game::items::equipment::Bodyplate::SetIType()
{
}

void game::items::equipment::Bodyplate::Use(Hero& h)
{
	//amount--;
}

int game::items::equipment::Bodyplate::GetEffect()
{
	return 0;
}

std::vector<game::items::equipment::Bodyplate*> game::items::equipment::GetBodyplates()
{
	std::vector<game::items::equipment::Bodyplate*>equipableBodyplate;

	equipableBodyplate.push_back(new game::items::equipment::bodyplate::IronBodyplate());

	return equipableBodyplate;
}