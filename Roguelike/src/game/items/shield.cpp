#include "shield.h"

game::items::Shield::Shield() noexcept
{
}

game::items::Shield::~Shield() noexcept
{
	// if connected
		// decrease hero defenses
}

void game::items::Shield::SetName()
{
	name = "Shield";
}

void game::items::Shield::SetEffect()
{
	effect = "Add an extra 10% defence possibility";
}

void game::items::Shield::Use(Hero* h)
{
	if (h->leftHandInUse)
	{
		h->extraDefenseChance -= 10;
		h->defenseChance -= 10;
		h->leftHandInUse = false;
	}
	else
	{
		h->extraDefenseChance += 10;
		h->defenseChance += 10;
		h->leftHandInUse = true;
	}
}