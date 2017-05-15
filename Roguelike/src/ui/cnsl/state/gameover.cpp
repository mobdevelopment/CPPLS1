#include "gameover.h"

using namespace ui::cnsl;
using namespace ui::cnsl::state;

const Type Gameover::TYPE(Type::GAMEOVER);

void Gameover::SaveCommandHandler(utils::cmd::Command& command)
{
	game::SaveHero(context.hero);

	context.userInterface.Exit();
}

void Gameover::Initialize()
{
	context.userInterface.GameOver();
	context.userInterface.RegisterCommand("Save", std::bind(&Gameover::SaveCommandHandler, this, std::placeholders::_1));
	context.userInterface.UnregisterCommand("Back");
	context.userInterface.UnregisterCommand("Exit");
}

void Gameover::Terminate()
{
	context.userInterface.UnregisterCommand("Save");
}

void Gameover::DrawConsole() const
{
	std::cout << std::endl << "Gameover" << std::endl << std::endl << "You have being killed" << std::endl;
}

void Gameover::GetAvailableCommands(std::vector<CommandDescription>& commandDescriptionsBuffer) const
{
	CommandDescription saveCommandDescription;
	saveCommandDescription.command = "Save";
	saveCommandDescription.description = "Save the hero stats and exit the game";

	commandDescriptionsBuffer.emplace_back(std::move(saveCommandDescription));
}
