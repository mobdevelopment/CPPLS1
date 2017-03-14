#ifndef GAME_NODES_STAIRSUP_HEADER_INCLUDED
#define GAME_NODES_STAIRSUP_HEADER_INCLUDED

#include "node.h"
#include "room.h"
#include "type.h"
#include "space.h"

namespace game
{
	namespace nodes
	{
		class Corridor;
		class HorizontalCorridor;
		class VerticalCorridor;
		class StairsDown;
		class Space;

		class StairsUp :
			public Node<StairsUp, Type::STAIRS_UP>,
			public Space
		{
		public:
			StairsDown* topRoom;

			unsigned int GetWeight() const override;

			StairsDown* GetTopRoom();
			void SetTopRoom(StairsDown* const room);

			std::string GetDescription() const;
		}; // class StairsUp
	} // namespace nodes 
} // namespace game

#endif // #ifndef GAME_NODES_STAIRSUP_HEADER_INCLUDED
