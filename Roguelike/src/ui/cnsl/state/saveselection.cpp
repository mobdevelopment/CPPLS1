#include "saveselection.h"

using namespace ui::cnsl;
using namespace ui::cnsl::state;

const Type SaveSelection::TYPE(Type::HERO_SELECTION);

void SaveSelection::SelectCommandHandler(utils::cmd::Command& command)
{
	std::string saveName = command.GetParameter<std::string>(0);

	// Check if the hero exists.
	if (saves.find(saveName) == saves.end())
	{
		context.userInterface.DrawConsole("Save '" + saveName + "' doesn't exist.");
		return;
	}

	// Load the active hero into the context.
	context.game = saves[saveName].game;
	context.hero = saves[saveName].game.GetHero();

	// Go to the dungeon selection state.
	context.userInterface.SetState(Type::DUNGEON_SELECTION);
}

void SaveSelection::Initialize()
{
	//saves = game::GetSavedSaves();

	// Register commands.
	context.userInterface.RegisterCommand<std::string>("Select", std::bind(&SaveSelection::SelectCommandHandler, this, std::placeholders::_1));
}

void SaveSelection::Terminate()
{
	// Unregister commands.
	context.userInterface.UnregisterCommand("Select");
}

void SaveSelection::DrawConsole() const
{
	std::cout << "Save selection" << std::endl;

	for (const auto& save : saves)
	{
		std::cout << std::endl << save.first << ", seed " << save.second.name; //.seed;
	}
}

void SaveSelection::GetAvailableCommands(std::vector<CommandDescription>& commandDescriptionsBuffer) const
{
	CommandDescription selectCommandDescription;
	selectCommandDescription.command = "Select";
	selectCommandDescription.description = "Select your save!";
	selectCommandDescription.parameters.emplace_back("date");

	commandDescriptionsBuffer.emplace_back(std::move(selectCommandDescription));
}