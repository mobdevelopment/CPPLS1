#ifndef GAME_NODES_HORIZONTALCORRIDOR_HEADER_INCLUDED
#define GAME_NODES_HORIZONTALCORRIDOR_HEADER_INCLUDED

#include "node.h"
#include "type.h"

#include "corridor.h"

namespace game
{
namespace nodes
{
	class Room;

	class HorizontalCorridor :
		public Node<HorizontalCorridor, Type::HORIZONTAL_CORRIDOR>,
		public Corridor
	{
	public:
		unsigned int GetWeight() const override;

		Room* GetEastRoom();
		Room* GetWestRoom();

		void SetEastRoom(Room* const room);
		void SetWestRoom(Room* const room);
	}; // class HorizontalCorridor
} // namespace nodes
} // namespace game

#endif // #ifndef GAME_NODES_HORIZONTALCORRIDOR_HEADER_INCLUDED
