#ifndef GAME_NODES_STAIRSUP_HEADER_INCLUDED
#define GAME_NODES_STAIRSUP_HEADER_INCLUDED

#include "node.h"
#include "room.h"
#include "type.h"

#include "stairsdown.h"

namespace game
{
	namespace nodes
	{
		class StairsDown;

		class StairsUp :
			public Node<StairsUp, Type::STAIRS_UP>
		{
		public:
			StairsDown* topRoom;

			unsigned int GetWeight() const override;

			StairsDown* GetTopRoom();
			void SetTopRoom(StairsDown* const room);
		}; // class StairsUp
	} // namespace nodes 
} // namespace game

#endif // #ifndef GAME_NODES_STAIRSUP_HEADER_INCLUDED
