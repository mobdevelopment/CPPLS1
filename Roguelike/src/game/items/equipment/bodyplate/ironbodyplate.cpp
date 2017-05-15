#include "ironbodyplate.h"

#include <boost\algorithm\string.hpp>

game::items::equipment::bodyplate::IronBodyplate::IronBodyplate() noexcept
{
}

game::items::equipment::bodyplate::IronBodyplate::~IronBodyplate() noexcept
{
	name.clear();
	description.clear();
	iType.clear();
}

void game::items::equipment::bodyplate::IronBodyplate::SetName()
{
	name = "IronBodyplate";
}

void game::items::equipment::bodyplate::IronBodyplate::SetDescription()
{
	description = "A simple Iron Bodyplate which boosts the hero's attackchance with 5%.";
}

void game::items::equipment::bodyplate::IronBodyplate::SetIType()
{
	iType = "Equipment";
}

int game::items::equipment::bodyplate::IronBodyplate::GetEffect()
{
	return 5;
}

void game::items::equipment::bodyplate::IronBodyplate::Use(Hero& h)
{
	if (h.body == nullptr)
	{
		h.body = this;
	}
	else
	{
		if (boost::iequals(h.body->name, name))
			h.body = nullptr;
		else
			h.body = this;
	}
}

