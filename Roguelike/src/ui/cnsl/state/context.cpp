#include "context.h"

ui::cnsl::state::Context::Context(UserInterface& userInterface, game::Game& game) noexcept :
	userInterface(userInterface),
	game(game)
{
}