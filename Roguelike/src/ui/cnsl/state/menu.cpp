#include "menu.h"

using namespace ui::cnsl;
using namespace ui::cnsl::state;

const Type Menu::TYPE(Type::MENU);

void Menu::Initialize()
{
	// Register commands.
	context.userInterface.RegisterCommand<>("NewHero", [this](const utils::cmd::Command& command) { context.userInterface.SetState(Type::HERO_CREATION); });
	context.userInterface.RegisterCommand<>("SelectHero", [this](const utils::cmd::Command& command) { context.userInterface.SetState(Type::HERO_SELECTION); });
}

void Menu::Terminate()
{
	// Unregister commands.
	context.userInterface.UnregisterCommand("NewHero");
	context.userInterface.UnregisterCommand("SelectHero");
}

void Menu::DrawConsole() const
{
	std::cout << "Menu";
}

void Menu::GetAvailableCommands(std::vector<CommandDescription>& commandDescriptionsBuffer) const
{
	CommandDescription newHeroCommandDescription;
	newHeroCommandDescription.command = "NewHero";
	newHeroCommandDescription.description = "Create a new hero.";

	CommandDescription selectHeroCommandDescription;
	selectHeroCommandDescription.command = "SelectHero";
	selectHeroCommandDescription.description = "Select a hero.";

	commandDescriptionsBuffer.emplace_back(std::move(newHeroCommandDescription));
	commandDescriptionsBuffer.emplace_back(std::move(selectHeroCommandDescription));
}
