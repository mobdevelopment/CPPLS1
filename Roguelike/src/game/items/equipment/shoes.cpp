#include "shoes.h"

#include "shoes/leathershoes.h"

game::items::equipment::Shoes::Shoes() noexcept
{
}

game::items::equipment::Shoes::~Shoes() noexcept
{
}

void game::items::equipment::Shoes::SetName()
{
}

void game::items::equipment::Shoes::SetDescription()
{
}

void game::items::equipment::Shoes::SetIType()
{
}

void game::items::equipment::Shoes::Use(Hero& h)
{
	//amount--;
}

int game::items::equipment::Shoes::GetEffect()
{
	return 0;
}

std::vector<game::items::equipment::Shoes*> game::items::equipment::GetShoes()
{
	std::vector<game::items::equipment::Shoes*>equipableShoes;

	equipableShoes.push_back(new game::items::equipment::shoes::LeatherShoes());

	return equipableShoes;
}