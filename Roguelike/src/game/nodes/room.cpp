#include "room.h"
#include "../items/item.h"
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

game::Monster* Room::GetMonster()
{
	return &monster;
}

void Room::SetMonster(game::Monster m)
{
	monster = m;
}

bool Room::HasMonster()
{
	return !monster.name.empty();
}

game::items::Item* Room::GetItem()
{
	return item;
}

void Room::SetItem(game::items::Item& i)
{
	item = &i;
}

void Room::ClearItem()
{
	item = nullptr;
}

bool Room::HasItem()
{
	if (item != nullptr)
		return !item->name.empty();

	return false;
}


