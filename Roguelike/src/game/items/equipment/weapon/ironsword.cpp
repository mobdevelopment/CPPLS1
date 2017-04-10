#include "ironsword.h"

game::items::equipment::weapon::IronSword::IronSword() noexcept
{
}

game::items::equipment::weapon::IronSword::~IronSword() noexcept
{
}

void game::items::equipment::weapon::IronSword::SetName()
{
	name = "IronSword";
}

void game::items::equipment::weapon::IronSword::SetDescription()
{
	description = "A simple Iron Sword which boosts the hero's damage with 2.";
}

void game::items::equipment::weapon::IronSword::SetIType()
{
	iType = "Equipment";
}

int game::items::equipment::weapon::IronSword::GetEffect()
{
	return 2;
}

void game::items::equipment::weapon::IronSword::Use(Hero& h)
{
	if (h.rightHand == nullptr)
	{
		h.rightHand = this;
	}
	else
	{
		if (h.rightHand->name == name)
			h.rightHand == nullptr;
		else
			h.rightHand = this;
	}
}

