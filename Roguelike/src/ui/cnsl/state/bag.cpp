#include "bag.h"

using namespace ui::cnsl;
using namespace ui::cnsl::state;

const Type Bag::TYPE(Type::BAG);

void Bag::BagCommandHandler(utils::cmd::Command& command)
{
	std::string itemName = command.GetParameter<std::string>(0);
	auto hero = context.game.GetHero();
	auto items = hero.GetItems();
	for (auto i : items) {
		if (i->amount > 0 && boost::iequals(i->name, itemName)) {
			i->Use(&hero);
		}
	}

	// Go to the dungeon selection state.
	context.userInterface.SetState(Type::BAG);
}




void Bag::Initialize()
{
	/*context.userInterface.RegisterCommand("Fight", std::bind(&Fight::FightCommandHandler, this, std::placeholders::_1));

	context.userInterface.RegisterCommand("Flee", [this](const utils::cmd::Command& command) { context.userInterface.SetState(Type::ROOM); });

	if (context.game.HasMonster())
		return;
	else
		context.userInterface.SetState(Type::ROOM);*/

	
	// Register commands.
	context.userInterface.RegisterCommand<std::string>("Use", std::bind(&Bag::BagCommandHandler, this, std::placeholders::_1));
}

void Bag::Terminate()
{
	// Unregister commands.
	context.userInterface.UnregisterCommand("Use");
}

void Bag::DrawConsole() const
{
	auto hero = context.game.GetHero();
	auto items = hero.GetItems();

	std::cout << "Bag" << std::endl << std::endl;

	if (items.size() > 0) {
		for (auto i : items) {
			if (i->amount > 0) {
				std::cout << "name: " << i->name << ", amount: " << i->amount << "x, description: " << i->description << std::endl;
			}
		}
	}
	else {
		std::cout << "The bag is currently empty";
	}
}

void Bag::GetAvailableCommands(std::vector<CommandDescription>& commandDescriptionsBuffer) const
{
	CommandDescription selectCommandDescription;
	selectCommandDescription.command = "Use";
	selectCommandDescription.description = "Use your item!";
	selectCommandDescription.parameters.emplace_back("item");

	commandDescriptionsBuffer.emplace_back(std::move(selectCommandDescription));
}
