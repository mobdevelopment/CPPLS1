#include "room.h"

using namespace ui::cnsl;
using namespace ui::cnsl::state;

const Type Room::TYPE(Type::ROOM);

void Room::Initialize()
{
	context.userInterface.RegisterCommand("Map", [this](const utils::cmd::Command& command) { context.userInterface.SetState(Type::MAP); });
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
