#include "bag.h"

using namespace ui::cnsl;
using namespace ui::cnsl::state;

const Type Bag::TYPE(Type::BAG);

void Bag::BagCommandHandler(utils::cmd::Command& command)
{
	std::string itemName = command.GetParameter<std::string>(0);
	auto &hero = context.hero;
	auto items = hero.GetItems();

	for (auto i : items) {
		if (auto* ci = dynamic_cast<game::items::Consumable*>(i))
		{
			if (ci->amount > 0 && boost::iequals(ci->name, itemName)) {
				i->Use(hero);
				break;
			}
		}
		else if (auto* ci = dynamic_cast<game::items::Equipment*>(i)) {
			i->Use(hero);
			break;
		}
	}

	//context.hero = hero;

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
	auto hero = context.hero;
	auto items = hero.GetItems();

	std::cout << "Bag" << std::endl << std::endl;

	if (items.size() > 0) {
		for (auto i : items) {
			if (auto* ci = dynamic_cast<game::items::Consumable*>(i))
			{
				if (ci->amount > 0) {
					std::cout << "name: " << ci->name << ", amount: " << ci->amount << "x, description: " << ci->description << std::endl;
				}
			}
			else if (auto* ci = dynamic_cast<game::items::Equipment*>(i))
			{
				if (i == hero.leftHand || i == hero.rightHand || i == hero.legs || i == hero.body || i == hero.feet)
				{
					std::cout << "You're using a " << ci->name << ", description: " << ci->description << std::endl;
				}
				else
				{
					std::cout << "name: " << ci->name << ", description: " << ci->description << std::endl;
				}
				
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
