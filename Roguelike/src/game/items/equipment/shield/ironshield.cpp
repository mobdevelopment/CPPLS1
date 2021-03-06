#include "ironshield.h"

#include <boost\algorithm\string.hpp>

game::items::equipment::shield::IronShield::IronShield() noexcept
{
}

game::items::equipment::shield::IronShield::~IronShield() noexcept
{
	name.clear();
	description.clear();
	iType.clear();
}

void game::items::equipment::shield::IronShield::SetName()
{
	name = "IronShield";
}

void game::items::equipment::shield::IronShield::SetDescription()
{
	description = "A simple Iron Shield which boosts the hero's defence chance with 5%.";
}

void game::items::equipment::shield::IronShield::SetIType()
{
	iType = "Equipment";
}

int game::items::equipment::shield::IronShield::GetEffect()
{
	return 5;
}

void game::items::equipment::shield::IronShield::Use(Hero& h)
{
	if (h.leftHand == nullptr)
	{
		h.leftHand = this;
	}
	else
	{
		if (boost::iequals(h.leftHand->name, name))
			h.leftHand = nullptr;
		else
			h.leftHand = this;
	}

	int x = 5;
}

