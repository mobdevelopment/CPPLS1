#include "ironsword.h"

#include <boost\algorithm\string.hpp>

game::items::equipment::weapon::IronSword::IronSword() noexcept
{
}

game::items::equipment::weapon::IronSword::~IronSword() noexcept
{
	name.clear();
	description.clear();
	iType.clear();
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
		if (boost::iequals(h.rightHand->name, name))
			h.rightHand == nullptr;
		else
			h.rightHand = this;
	}
}

