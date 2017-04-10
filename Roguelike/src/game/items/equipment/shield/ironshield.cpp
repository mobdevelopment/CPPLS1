#include "ironshield.h"

game::items::equipment::shield::IronShield::IronShield() noexcept
{
}

game::items::equipment::shield::IronShield::~IronShield() noexcept
{
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
		if (h.leftHand->name == name)
			h.leftHand == nullptr;
		else
			h.leftHand = this;
	}

	int x = 5;
}

