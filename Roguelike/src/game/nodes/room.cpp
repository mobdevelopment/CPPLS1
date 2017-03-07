#include "room.h"
#include "horizontalcorridor.h"
#include "verticalcorridor.h"

using namespace game::nodes;

const std::string& game::nodes::GetRoomSizeDescription(const RoomSize roomSize)
{
	return ROOM_SIZE_DESCRIPTIONS[(int)roomSize];
}

const std::string& game::nodes::GetRoomCleanlinessDescription(const RoomCleanliness roomCleanliness)
{
	return ROOM_CLEANLINESS_DESCRIPTIONS[(int)roomCleanliness];
}

const std::string& game::nodes::GetRoomFurnitureDescription(const RoomFurniture roomFurniture)
{
	return ROOM_FURNITURE_DESCRIPTIONS[(int)roomFurniture];
}

Room::Room()
{
	roomSize = (RoomSize)(rand() % 3);
	roomCleanliness = (RoomCleanliness)(rand() % 2);
	roomFurniture = (RoomFurniture)(rand() % 3);
}

unsigned int Room::GetWeight() const
{
	return 1;
}

std::vector<Corridor*> Room::GetConnectedCorridors() const
{
	std::vector<Corridor*> corridors;

	if (northCorridor != nullptr && !northCorridor->collapsed)
		corridors.push_back(northCorridor);
	if (eastCorridor != nullptr && !eastCorridor->collapsed)
		corridors.push_back(eastCorridor);
	if (southCorridor != nullptr && !southCorridor->collapsed)
		corridors.push_back(southCorridor);
	if (westCorridor != nullptr && !westCorridor->collapsed)
		corridors.push_back(westCorridor);

	return corridors;
}

std::vector<Room*> Room::GetConnectedRooms() const
{
	std::vector<Room*> rooms;

	if (northCorridor != nullptr && northCorridor->GetNorthRoom() != nullptr && !northCorridor->collapsed)
		rooms.push_back(northCorridor->GetNorthRoom());
	if (eastCorridor != nullptr && eastCorridor->GetEastRoom() != nullptr && !eastCorridor->collapsed)
		rooms.push_back(eastCorridor->GetEastRoom());
	if (southCorridor != nullptr && southCorridor->GetSouthRoom() != nullptr && !southCorridor->collapsed)
		rooms.push_back(southCorridor->GetSouthRoom());
	if (westCorridor != nullptr && westCorridor->GetWestRoom() != nullptr && !westCorridor->collapsed)
		rooms.push_back(westCorridor->GetWestRoom());

	return rooms;
}

std::string Room::GetDescription() const
{
	std::stringstream stream;

	stream << "It's a " << GetRoomSizeDescription(roomSize) <<
		' ' << GetRoomCleanlinessDescription(roomCleanliness) <<
		" room";

	if (roomFurniture == RoomFurniture::EMPTY)
	{
		stream << ". There's nothing else in here.";
	}
	else
	{
		stream << ", with in the corner a " << GetRoomFurnitureDescription(roomFurniture) << '.';
	}

	return stream.str();
}
