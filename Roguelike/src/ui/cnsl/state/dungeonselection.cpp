#include "dungeonselection.h"

using namespace ui::cnsl;
using namespace ui::cnsl::state;

const Type DungeonSelection::TYPE(Type::DUNGEON_SELECTION);

void DungeonSelection::StartCommandHandler(utils::cmd::Command& command)
{

	context.hero.lifePoints = context.hero.maxLifePoints;
	context.game.RandomizeDungeon(dungeonLayers, dungeonWidth, dungeonHeight, dungeonSeed);
	context.game.SetHero(context.hero);
	context.game.Start();

	//// SAVESTATE::
	//game::Save save;
	//// set dungeon info
	//save.seed = dungeonSeed;
	//save.height = dungeonHeight;
	//save.width = dungeonWidth;
	//save.layers = dungeonLayers;
	//// set hero name
	//save.heroName = context.hero.name;

	context.userInterface.SetState(Type::ROOM);
}

void DungeonSelection::SetDungeonValueCommandHandler(utils::cmd::Command& command, unsigned int* const value)
{
	*value = command.GetParameter<unsigned int>(0);

	context.userInterface.DrawConsole();
}

void DungeonSelection::Initialize()
{
	// Default dungeon values.
	dungeonLayers	= 5;
	dungeonWidth	= 10;
	dungeonHeight	= 10;
	dungeonSeed		= std::random_device()();

	// Register commands.
	context.userInterface.RegisterCommand<unsigned int>("Layers", std::bind(&DungeonSelection::SetDungeonValueCommandHandler, this, std::placeholders::_1, &dungeonLayers));
	context.userInterface.RegisterCommand<unsigned int>("Width", std::bind(&DungeonSelection::SetDungeonValueCommandHandler, this, std::placeholders::_1, &dungeonWidth));
	context.userInterface.RegisterCommand<unsigned int>("Height", std::bind(&DungeonSelection::SetDungeonValueCommandHandler, this, std::placeholders::_1, &dungeonHeight));
	context.userInterface.RegisterCommand<unsigned int>("Seed", std::bind(&DungeonSelection::SetDungeonValueCommandHandler, this, std::placeholders::_1, &dungeonSeed));
	context.userInterface.RegisterCommand("Start", std::bind(&DungeonSelection::StartCommandHandler, this, std::placeholders::_1));
}

void DungeonSelection::Terminate()
{
	// Unregister commands.
	context.userInterface.UnregisterCommand("Layers");
	context.userInterface.UnregisterCommand("Width");
	context.userInterface.UnregisterCommand("Height");
	context.userInterface.UnregisterCommand("Seed");
	context.userInterface.UnregisterCommand("Start");
}

void DungeonSelection::DrawConsole() const
{
	std::cout << "Dungeon selection" << std::endl << std::endl

		<< "Dungeon layers: " << dungeonLayers << std::endl
		<< "Dungeon width: " << dungeonWidth << std::endl
		<< "Dungeon height: " << dungeonHeight << std::endl
		<< "Dungeon seed: " << dungeonSeed;
}

void DungeonSelection::GetAvailableCommands(std::vector<CommandDescription>& commandDescriptionsBuffer) const
{
	CommandDescription layersCommandDescription;
	layersCommandDescription.command = "Layers";
	layersCommandDescription.description = "Set the dungeon layers.";
	layersCommandDescription.parameters.emplace_back("layers");

	CommandDescription widthCommandDescription;
	widthCommandDescription.command = "Width";
	widthCommandDescription.description = "Set the dungeon width.";
	widthCommandDescription.parameters.emplace_back("width");

	CommandDescription heightCommandDescription;
	heightCommandDescription.command = "Height";
	heightCommandDescription.description = "Set the dungeon height.";
	heightCommandDescription.parameters.emplace_back("height");

	CommandDescription seedCommandDescription;
	seedCommandDescription.command = "Seed";
	seedCommandDescription.description = "Set the dungeon seed.";
	seedCommandDescription.parameters.emplace_back("seed");

	CommandDescription startCommandDescription;
	startCommandDescription.command = "Start";
	startCommandDescription.description = "Start the game!";

	commandDescriptionsBuffer.emplace_back(std::move(layersCommandDescription));
	commandDescriptionsBuffer.emplace_back(std::move(widthCommandDescription));
	commandDescriptionsBuffer.emplace_back(std::move(heightCommandDescription));
	commandDescriptionsBuffer.emplace_back(std::move(seedCommandDescription));
	commandDescriptionsBuffer.emplace_back(std::move(startCommandDescription));
}