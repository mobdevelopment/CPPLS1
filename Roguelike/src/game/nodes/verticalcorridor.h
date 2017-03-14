#ifndef GAME_NODES_VERTICALCORRIDOR_HEADER_INCLUDED
#define GAME_NODES_VERTICALCORRIDOR_HEADER_INCLUDED

#include "node.h"
#include "type.h"

#include "space.h"
#include "corridor.h"


namespace game
{
namespace nodes
{
	class Space;
	class Corridor;

	class VerticalCorridor:
		public Node<VerticalCorridor, Type::VERTICAL_CORRIDOR>,
		public Corridor
	{
	public:
		unsigned int GetWeight() const override;

		Space* GetNorthRoom();
		Space* GetSouthRoom();

		void SetNorthRoom(Space* const room);
		void SetSouthRoom(Space* const room);
	}; // class VerticalCorridor
} // namespace nodes
} // namespace game

#endif // #ifndef GAME_NODES_VERTICALCORRIDOR_HEADER_INCLUDED
