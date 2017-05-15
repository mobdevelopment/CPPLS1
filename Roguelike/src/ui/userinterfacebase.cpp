#include "userinterfacebase.h"

ui::UserInterfaceBase::UserInterfaceBase(game::Game& game) noexcept :
	game(game)
{
}

ui::UserInterfaceBase::~UserInterfaceBase() noexcept = default;
