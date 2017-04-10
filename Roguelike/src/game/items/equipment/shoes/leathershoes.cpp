#include "leathershoes.h"

game::items::equipment::shoes::LeatherShoes::LeatherShoes() noexcept
{
}

game::items::equipment::shoes::LeatherShoes::~LeatherShoes() noexcept
{
}

void game::items::equipment::shoes::LeatherShoes::SetName()
{
	name = "LeatherShoes";
}

void game::items::equipment::shoes::LeatherShoes::SetDescription()
{
	description = "A simple leather shoes which boosts the hero's amount of attack with 1.";
}

void game::items::equipment::shoes::LeatherShoes::SetIType()
{
	iType = "Equipment";
}

int game::items::equipment::shoes::LeatherShoes::GetEffect()
{
	return 1;
}

void game::items::equipment::shoes::LeatherShoes::Use(Hero& h)
{
	if (h.feet == nullptr)
	{
		h.feet = this;
	}
	else
	{
		if (h.feet->name == name)
			h.feet == nullptr;
		else
			h.feet = this;
	}
}

