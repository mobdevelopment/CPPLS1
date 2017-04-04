#include "bag.h"

using namespace ui::cnsl;
using namespace ui::cnsl::state;

const Type Bag::TYPE(Type::BAG);

void Bag::BagCommandHandler(utils::cmd::Command& command)
{
	std::string itemName = command.GetParameter<std::string>(0);

	// Check if the hero exists.
	/*if (items.find(itemName) == items.end())
	{
		context.userInterface.DrawConsole("Item '" + itemName + "' doesn't exist.");
		return;
	}*/

	// use item
	//context.hero.

	// Go to the dungeon selection state.
	//context.userInterface.SetState(Type::DUNGEON_SELECTION);

	// Go to the dungeon selection state.
	//context.userInterface.SetState(Type::BAG);
}




void Bag::Initialize()
{
	/*context.userInterface.RegisterCommand("Fight", std::bind(&Fight::FightCommandHandler, this, std::placeholders::_1));

	context.userInterface.RegisterCommand("Flee", [this](const utils::cmd::Command& command) { context.userInterface.SetState(Type::ROOM); });

	if (context.game.HasMonster())
		return;
	else
		context.userInterface.SetState(Type::ROOM);*/

	auto items = context.hero.items;

	// Register commands.
	context.userInterface.RegisterCommand<std::string>("Select", std::bind(&Bag::BagCommandHandler, this, std::placeholders::_1));
}

void Bag::Terminate()
{
	// Unregister commands.
	context.userInterface.UnregisterCommand("Select");
}

void Bag::DrawConsole() const
{
	/*auto i = context.game.GetHero().items;
	std::cout << std::endl << "You have " << i.size() << " items in your bag" << std::endl;*/

	/*std::cout << "Item selection" << std::endl;

	for (const auto& item : items)
	{
		std::cout << std::endl << item.name << ", amount: " << item.amount << ", effect: " << item.effect;
	}*/
}

void Bag::GetAvailableCommands(std::vector<CommandDescription>& commandDescriptionsBuffer) const
{
	CommandDescription selectCommandDescription;
	selectCommandDescription.command = "Select";
	selectCommandDescription.description = "Select your item!";
	selectCommandDescription.parameters.emplace_back("item");

	commandDescriptionsBuffer.emplace_back(std::move(selectCommandDescription));
}
