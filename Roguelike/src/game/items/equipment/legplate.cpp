#include "legplate.h"

#include "legplate/ironlegplate.h"

game::items::equipment::Legplate::Legplate() noexcept
{
}

game::items::equipment::Legplate::~Legplate() noexcept
{
}

void game::items::equipment::Legplate::SetName()
{
}

void game::items::equipment::Legplate::SetDescription()
{
}

void game::items::equipment::Legplate::SetIType()
{
}

void game::items::equipment::Legplate::Use(Hero& h)
{
	//amount--;
}

int game::items::equipment::Legplate::GetEffect()
{
	return 0;
}

std::vector<game::items::equipment::Legplate*> game::items::equipment::GetLegplates()
{
	std::vector<game::items::equipment::Legplate*>equipableLegplate;

	equipableLegplate.push_back(new game::items::equipment::legplate::IronLegplate());

	return equipableLegplate;
}