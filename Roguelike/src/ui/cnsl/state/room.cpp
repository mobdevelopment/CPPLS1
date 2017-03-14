#include "room.h"

using namespace ui::cnsl;
using namespace ui::cnsl::state;

const Type Room::TYPE(Type::ROOM);

void Room::SelectCommandHandler(utils::cmd::Command& command)
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

	context.userInterface.RegisterCommand<std::string>("Move", std::bind(&Room::SelectCommandHandler, this, std::placeholders::_1));
}

void Room::Terminate()
{
	context.userInterface.UnregisterCommand("Map");
}

void Room::DrawConsole() const
{
	std::cout << "Room" << std::endl << std::endl

		<< "Description: " << context.game.GetHeroLocation()->GetDescription() << std::endl;
	
}

void Room::GetAvailableCommands(std::vector<CommandDescription>& commandDescriptionsBuffer) const
{
	CommandDescription mapCommandDescription;
	mapCommandDescription.command = "Map";
	mapCommandDescription.description = "Look at the map.";

	commandDescriptionsBuffer.emplace_back(std::move(mapCommandDescription));
}
