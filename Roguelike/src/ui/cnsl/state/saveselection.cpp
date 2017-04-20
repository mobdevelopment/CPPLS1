#include "saveselection.h"

using namespace ui::cnsl;
using namespace ui::cnsl::state;

const Type SaveSelection::TYPE(Type::SAVE_SELECTION);

void SaveSelection::SelectCommandHandler(utils::cmd::Command& command)
{
	std::string saveName = command.GetParameter<std::string>(0);

	// Check if the hero exists.
	if (saves.find(saveName) == saves.end())
	{
		context.userInterface.DrawConsole("Save '" + saveName + "' doesn't exist.");
		return;
	}

	game::HeroesContainer heroes = game::GetSavedHeroes();
	if (heroes.find(saves[saveName].heroName) == heroes.end())
	{
		context.userInterface.DrawConsole("Save data is corrupt! Hero '" + saves[saveName].heroName + "' doesn't exist.");
		return;
	}

	// Load the active hero into the context.
	context.hero = heroes[saves[saveName].heroName];
	context.hero.lifePoints = context.hero.maxLifePoints;
	context.hero.AddItems(saves[saveName].bag);
	context.hero.AddEquipables(saves[saveName].equipment);

	context.game.RandomizeDungeon(saves[saveName].layers, saves[saveName].width, saves[saveName].height, saves[saveName].seed);
	context.game.SetHero(context.hero);
	context.game.Start(saves[saveName].startX, saves[saveName].startY, saves[saveName].startZ);

	context.game.AddMonsters(saves[saveName].monsters);
	context.game.AddItems(saves[saveName].items);

	// Go to the dungeon selection state.
	context.userInterface.SetState(Type::ROOM);
}

void SaveSelection::Initialize()
{
	saves = game::GetSavedSaves();

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
		std::cout << std::endl << save.first << ", seed " << save.second.name;
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