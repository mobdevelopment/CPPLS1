#ifndef GAME_NODES_VERTICALCORRIDOR_HEADER_INCLUDED
#define GAME_NODES_VERTICALCORRIDOR_HEADER_INCLUDED

#include "node.h"
#include "type.h"

#include "corridor.h"

namespace game
{
namespace nodes
{
	class Room;

	class VerticalCorridor:
		public Node<VerticalCorridor, Type::VERTICAL_CORRIDOR>,
		public Corridor
	{
	public:
		unsigned int GetWeight() const override;

		Room* GetNorthRoom();
		Room* GetSouthRoom();

		void SetNorthRoom(Room* const room);
		void SetSouthRoom(Room* const room);
	}; // class VerticalCorridor
} // namespace nodes
} // namespace game

#endif // #ifndef GAME_NODES_VERTICALCORRIDOR_HEADER_INCLUDED
