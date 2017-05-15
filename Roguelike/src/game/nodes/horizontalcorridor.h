#ifndef GAME_NODES_HORIZONTALCORRIDOR_HEADER_INCLUDED
#define GAME_NODES_HORIZONTALCORRIDOR_HEADER_INCLUDED

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

	class HorizontalCorridor :
		public Node<HorizontalCorridor, Type::HORIZONTAL_CORRIDOR>,
		public Corridor
	{
	public:
		unsigned int GetWeight() const override;

		Space* GetEastRoom();
		Space* GetWestRoom();

		void SetEastRoom(Space* const room);
		void SetWestRoom(Space* const room);
	}; // class HorizontalCorridor
} // namespace nodes
} // namespace game

#endif // #ifndef GAME_NODES_HORIZONTALCORRIDOR_HEADER_INCLUDED
