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

void game::items::equipment::Shield::Use(Hero& h)
{

}

int game::items::equipment::Shield::GetEffect()
{
	return 0;
}

std::vector<game::items::equipment::Shield*> game::items::equipment::GetShields()
{
	std::vector<game::items::equipment::Shield*>equipableShields;

	equipableShields.push_back(new items::equipment::shield::IronShield());

	return equipableShields;
}