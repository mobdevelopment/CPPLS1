#ifndef GAME_NODES_ROOM_HEADER_INCLUDED
#define GAME_NODES_ROOM_HEADER_INCLUDED

#include <vector>
#include <sstream>
#include <string>

#include "node.h"
#include "type.h"

#include "space.h"

namespace game
{
namespace nodes
{
	class Corridor;
	class HorizontalCorridor;
	class VerticalCorridor;
	class Space;

	enum class RoomSize
	{
		LARGE,
		MEDIUM,
		SMALL
	};

	static const std::string ROOM_SIZE_DESCRIPTIONS[] =
	{
		"large",
		"medium",
		"small"
	};

	enum class RoomCleanliness
	{
		CLEAN,
		DIRTY
	};

	static const std::string ROOM_CLEANLINESS_DESCRIPTIONS[] =
	{
		"clean",
		"dirty"
	};

	enum class RoomFurniture
	{
		EMPTY,
		TABLE,
		BED
	};

	static const std::string ROOM_FURNITURE_DESCRIPTIONS[] =
	{
		"empty",
		"table with four chairs",
		"bed"
	};

	const std::string& GetRoomSizeDescription(const RoomSize roomSize);
	const std::string& GetRoomCleanlinessDescription(const RoomCleanliness roomCleanliness);
	const std::string& GetRoomFurnitureDescription(const RoomFurniture roomFurniture);

	class Room :
		public Node<Room, Type::ROOM>,
		public Space
	{
	public:
		RoomSize			roomSize;
		RoomCleanliness		roomCleanliness;
		RoomFurniture		roomFurniture;

		Room();

		unsigned int GetWeight() const override;

		std::string GetDescription() const;
	};
} // namespace nodes
} // namespace game

#endif // #ifndef GAME_NODES_ROOM_HEADER_INCLUDED
