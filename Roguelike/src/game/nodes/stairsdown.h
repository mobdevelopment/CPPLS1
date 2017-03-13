#ifndef GAME_NODES_STAIRSDOWN_HEADER_INCLUDED
#define GAME_NODES_STAIRSDOWN_HEADER_INCLUDED

#include "node.h"
#include "room.h"
#include "type.h"
#include "stairsup.h"

namespace game
{
	namespace nodes
	{
		class StairsUp;

		class StairsDown :
			public Node<StairsDown, Type::STAIRS_DOWN>
		{
		public:
			StairsUp* bottomRoom;

			unsigned int GetWeight() const override;

			StairsUp* GetBottomRoom() const;
			void SetBottomRoom(StairsUp* const room);
		}; // class StairsDown
	} // namespace nodes
} // namespace game

#endif // #ifndef GAME_NODES_STAIRSDOWN_HEADER_INCLUDED
