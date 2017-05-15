#include "heroselection.h"

using namespace ui::cnsl;
using namespace ui::cnsl::state;

const Type HeroSelection::TYPE(Type::HERO_SELECTION);

void HeroSelection::SelectCommandHandler(utils::cmd::Command& command)
{
	std::string heroName = command.GetParameter<std::string>(0);

	// Check if the hero exists.
	if (heroes.find(heroName) == heroes.end())
	{
		context.userInterface.DrawConsole("Hero '" + heroName + "' doesn't exist.");
		return;
	}

	// Load the active hero into the context.
	context.hero = heroes[heroName];

	// Go to the dungeon selection state.
	context.userInterface.SetState(Type::DUNGEON_SELECTION);
}

void HeroSelection::Initialize()
{
	heroes = game::GetSavedHeroes();

	// Register commands.
	context.userInterface.RegisterCommand<std::string>("Select", std::bind(&HeroSelection::SelectCommandHandler, this, std::placeholders::_1));
}

void HeroSelection::Terminate()
{
	// Unregister commands.
	context.userInterface.UnregisterCommand("Select");
}

void HeroSelection::DrawConsole() const
{
	std::cout << "Hero selection" << std::endl;

	for (const auto& hero : heroes)
	{
		std::cout << std::endl << hero.first << ", level " << hero.second.level;
	}
}

void HeroSelection::GetAvailableCommands(std::vector<CommandDescription>& commandDescriptionsBuffer) const
{
	CommandDescription selectCommandDescription;
	selectCommandDescription.command = "Select";
	selectCommandDescription.description = "Select your hero!";
	selectCommandDescription.parameters.emplace_back("name");

	commandDescriptionsBuffer.emplace_back(std::move(selectCommandDescription));
}