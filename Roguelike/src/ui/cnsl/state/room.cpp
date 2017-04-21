#include "room.h"

using namespace ui::cnsl;
using namespace ui::cnsl::state;

const Type Room::TYPE(Type::ROOM);

void Room::SaveCommandHandler(utils::cmd::Command& command)
{
	game::SaveHero(context.hero);
	context.userInterface.Exit();
}

void Room::GrabCommandHandler(utils::cmd::Command& command)
{
	if (auto* room = dynamic_cast<game::nodes::Room*>(context.game.GetHeroLocation()))
	{
		auto item = room->GetItem();
		if (auto consumable = dynamic_cast<game::items::Consumable*>(item))
		{
			context.hero.AddItem(consumable);
			room->ClearItem();
		}
		else if (auto equipable = dynamic_cast<game::items::Equipment*>(item))
		{
			bool hasItem = false;
			for (auto i : context.hero.GetItems())
			{
				if (i->name == equipable->name)
					hasItem = true;
			}

			if (!hasItem)
			{
				context.hero.AddItem(equipable);
				room->ClearItem();
			}
			else
			{
				context.userInterface.DrawConsole("you already have a " + item->name + ", you don't have room for a second");
				return;
			}
		}

		context.userInterface.DrawConsole(item->name + " grabbed");
		context.game.OnChange();
		return;
	}

	context.userInterface.SetState(Type::ROOM);
}

void Room::MoveCommandHandler(utils::cmd::Command& command)
{
	std::string direction = command.GetParameter<std::string>(0);

	// Check if the hero exists.
	if (direction == "up" || direction == "down" || direction == "left" || direction == "right")
	{
		auto currentLocation = context.game.GetHeroLocation();
		if (direction == "up" && currentLocation->southCorridor != nullptr && !currentLocation->southCorridor->collapsed) // The y-axis is reversed
		{
			context.game.MoveUp();
		}
		else if (direction == "down" && currentLocation->northCorridor != nullptr && !currentLocation->northCorridor->collapsed) // The y-axis is reversed
		{
			context.game.MoveDown();
		}
		else if (direction == "left" && currentLocation->westCorridor != nullptr && !currentLocation->westCorridor->collapsed)
		{
			context.game.MoveLeft();
		}
		else if (direction == "right" && currentLocation->eastCorridor != nullptr && !currentLocation->eastCorridor->collapsed)
		{
			context.game.MoveRight();
		}
		else
		{
			context.userInterface.DrawConsole("This direction is unavailable in this room");
			return;
		}
	}
	else
	{
		context.userInterface.DrawConsole("Use a valid direction, Available options are: up, down, left, right");
		return;
	}
	// Go to the dungeon selection state.
	context.userInterface.SetState(Type::ROOM);
}

void Room::Initialize()
{
	context.userInterface.RegisterCommand("Map", [this](const utils::cmd::Command& command) { context.userInterface.SetState(Type::MAP); });

	context.userInterface.RegisterCommand<std::string>("Move", std::bind(&Room::MoveCommandHandler, this, std::placeholders::_1));

	context.userInterface.RegisterCommand("Grab", std::bind(&Room::GrabCommandHandler, this, std::placeholders::_1));

	context.userInterface.RegisterCommand("Fight", [this](const utils::cmd::Command& command) { context.userInterface.SetState(Type::FIGHT);  });

	context.userInterface.RegisterCommand("Bag", [this](const utils::cmd::Command& command) { context.userInterface.SetState(Type::BAG);  });

	context.userInterface.RegisterCommand("Save", std::bind(&Room::SaveCommandHandler, this, std::placeholders::_1));
}

void Room::Terminate()
{
	context.userInterface.UnregisterCommand("Map");
	context.userInterface.UnregisterCommand("Move");
	context.userInterface.UnregisterCommand("Fight");
	context.userInterface.UnregisterCommand("Bag");
	context.userInterface.UnregisterCommand("Grab");
	context.userInterface.UnregisterCommand("Save");
}

void Room::DrawConsole() const
{
	std::cout << "Room" << std::endl << std::endl

		<< "Description: " << context.game.GetHeroLocation()->GetDescription() << std::endl;

	if (auto* room = dynamic_cast<game::nodes::Room*>(context.game.GetHeroLocation()))
	{
		if (room->HasMonster())
		{
			if (room->GetMonster()->lifePoints > 0)
				std::cout << std::endl << "There is a : " << room->GetMonster()->name << " in this room" << std::endl;
			else
				std::cout << std::endl << "There is a deceased " << room->GetMonster()->name << " in this room" << std::endl;
		}
		//TODO::
		// check if item was already picked up
		if (room->HasItem() && !room->IsItemPickedUp()) {
			std::cout << std::endl << "You found a : " << room->GetItem()->name << "!" << std::endl;
		}
	}
}

void Room::GetAvailableCommands(std::vector<CommandDescription>& commandDescriptionsBuffer) const
{
	CommandDescription mapCommandDescription;
	mapCommandDescription.command = "Map";
	mapCommandDescription.description = "Look at the map.";

	commandDescriptionsBuffer.emplace_back(std::move(mapCommandDescription));

	CommandDescription moveCommandDescription;
	moveCommandDescription.command = "Move";
	moveCommandDescription.description = "Move in a specific direction";

	auto currentLocation = context.game.GetHeroLocation();

	if (currentLocation->southCorridor != nullptr && !currentLocation->southCorridor->collapsed) // The y-axis is reversed
		moveCommandDescription.parameters.emplace_back("up");
	if (currentLocation->northCorridor != nullptr && !currentLocation->northCorridor->collapsed) // The y-axis is reversed
		moveCommandDescription.parameters.emplace_back("down");
	if (currentLocation->westCorridor != nullptr && !currentLocation->westCorridor->collapsed)
		moveCommandDescription.parameters.emplace_back("left");
	if (currentLocation->eastCorridor != nullptr && !currentLocation->eastCorridor->collapsed)
		moveCommandDescription.parameters.emplace_back("right");

	commandDescriptionsBuffer.emplace_back(std::move(moveCommandDescription));

	if (auto room = dynamic_cast<game::nodes::Room*>(context.game.GetHeroLocation()))
	{
		if (room->HasMonster() && room->GetMonster()->lifePoints > 0)
		{
			CommandDescription fightCommandDescription;
			fightCommandDescription.command = "fight";
			fightCommandDescription.description = "Fight the monster in this room";

			commandDescriptionsBuffer.emplace_back(std::move(fightCommandDescription));
		}
		if (room->HasItem() && !room->IsItemPickedUp())
		{
			CommandDescription grabCommandDescription;
			grabCommandDescription.command = "Grab";
			grabCommandDescription.description = "Grab the item in this room";

			commandDescriptionsBuffer.emplace_back(std::move(grabCommandDescription));
		}
	}
	
	CommandDescription itemCommandDescription;
	itemCommandDescription.command = "Bag";
	itemCommandDescription.description = "Use an item from your bag";
	commandDescriptionsBuffer.emplace_back(std::move(itemCommandDescription));

	CommandDescription saveCommandDescription;
	saveCommandDescription.command = "Save";
	saveCommandDescription.description = "Save the hero stats and exit the game";

	commandDescriptionsBuffer.emplace_back(std::move(saveCommandDescription));
}
