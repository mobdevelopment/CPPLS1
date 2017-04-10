#include "shield.h"

#include "shield\ironshield.h"

game::items::equipment::Shield::Shield() noexcept
{
}

game::items::equipment::Shield::~Shield() noexcept
{
	// if connected
		// decrease hero defenses
}

void game::items::equipment::Shield::SetName()
{
	//name = "Shield";
}

void game::items::equipment::Shield::SetDescription()
{
	//description = "Add an extra 10% defence possibility";
}

void game::items::equipment::Shield::SetIType()
{
	
}

void game::items::equipment::Shield::Use(Hero* h)
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

std::vector<game::items::equipment::Shield*> game::items::equipment::GetShields()
{
	std::vector<game::items::equipment::Shield*>equipableShields;

	equipableShields.push_back(new game::items::equipment::shield::IronShield());

	return equipableShields;
}