#include "herocreation.h"

using namespace ui::cnsl;
using namespace ui::cnsl::state;

const Type HeroCreation::TYPE(Type::HERO_CREATION);

void HeroCreation::NameCommandHandler(utils::cmd::Command& command)
{
	hero.name = std::move(command.GetParameter<std::string>(0));
	context.userInterface.DrawConsole();
}

void HeroCreation::RandomNameCommandHandler(utils::cmd::Command& command)
{
	hero.name = game::GetRandomHeroName();
	context.userInterface.DrawConsole();
}

void HeroCreation::SaveCommandHandler(utils::cmd::Command& command)
{
	game::SaveHero(hero);
	context.userInterface.SetState(Type::HERO_SELECTION);
}

void HeroCreation::Initialize()
{
	// Default new hero values.
	hero.name = game::GetRandomHeroName();
	hero.level = 1;
	hero.lifePoints = 10;
	hero.experiencePoints = 0;
	hero.attackPoints = 0;
	hero.defensePoints = 0;

	// Register commands.
	context.userInterface.RegisterCommand<std::string>("Name", std::bind(&HeroCreation::NameCommandHandler, this, std::placeholders::_1));
	context.userInterface.RegisterCommand<>("RandomName", std::bind(&HeroCreation::RandomNameCommandHandler, this, std::placeholders::_1));
	context.userInterface.RegisterCommand<>("Save", std::bind(&HeroCreation::SaveCommandHandler, this, std::placeholders::_1));
}

void HeroCreation::Terminate()
{
	// Unregister commands.
	context.userInterface.UnregisterCommand("Name");
	context.userInterface.UnregisterCommand("RandomName");
	context.userInterface.UnregisterCommand("Save");
}

void HeroCreation::DrawConsole() const
{
	std::cout << "Hero creation" << std::endl << std::endl

		<< "Name: " << hero.name << std::endl
		<< "Level: " << hero.level << std::endl
		<< "Life points: " << hero.lifePoints << std::endl
		<< "Experience points: " << hero.experiencePoints << std::endl
		<< "Attack points: " << hero.attackPoints << std::endl
		<< "Defense points: " << hero.defensePoints;
}

void HeroCreation::GetAvailableCommands(std::vector<CommandDescription>& commandDescriptionsBuffer) const
{
	CommandDescription nameCommandDescription;
	nameCommandDescription.command = "Name";
	nameCommandDescription.description = "Give your hero a name.";
	nameCommandDescription.parameters.emplace_back("name");

	CommandDescription randomNameCommandDescription;
	randomNameCommandDescription.command = "RandomName";
	randomNameCommandDescription.description = "Give your hero a random name.";

	CommandDescription saveCommandDescription;
	saveCommandDescription.command = "Save";
	saveCommandDescription.description = "Save this hero and go to the hero selection screen.";

	commandDescriptionsBuffer.emplace_back(std::move(nameCommandDescription));
	commandDescriptionsBuffer.emplace_back(std::move(randomNameCommandDescription));
	commandDescriptionsBuffer.emplace_back(std::move(saveCommandDescription));
}