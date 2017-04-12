#include "ironlegplate.h"

game::items::equipment::legplate::IronLegplate::IronLegplate() noexcept
{
}

game::items::equipment::legplate::IronLegplate::~IronLegplate() noexcept
{
	name.clear();
	description.clear();
	iType.clear();
}

void game::items::equipment::legplate::IronLegplate::SetName()
{
	name = "IronLegplate";
}

void game::items::equipment::legplate::IronLegplate::SetDescription()
{
	description = "A simple Iron Legplate which boosts the hero's damage with 5%.";
}

void game::items::equipment::legplate::IronLegplate::SetIType()
{
	iType = "Equipment";
}

int game::items::equipment::legplate::IronLegplate::GetEffect()
{
	return 5;
}

void game::items::equipment::legplate::IronLegplate::Use(Hero& h)
{
	if (h.legs == nullptr)
	{
		h.legs = this;
	}
	else
	{
		if (h.legs->name == name)
			h.legs == nullptr;
		else
			h.legs = this;
	}
}

