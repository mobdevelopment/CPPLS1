#ifndef GAME_NODES_STAIRSDOWN_HEADER_INCLUDED
#define GAME_NODES_STAIRSDOWN_HEADER_INCLUDED

#include "node.h"
#include "room.h"
#include "type.h"
#include "space.h"

namespace game
{
	namespace nodes
	{
		class StairsUp;
		class Space;

		class StairsDown :
			public Node<StairsDown, Type::STAIRS_DOWN>,
			public Space
		{
		public:
			StairsUp* bottomRoom;

			unsigned int GetWeight() const override;

			StairsUp* GetBottomRoom() const;
			void SetBottomRoom(StairsUp* const room);

			std::string GetDescription() const;
		}; // class StairsDown
	} // namespace nodes
} // namespace game

#endif // #ifndef GAME_NODES_STAIRSDOWN_HEADER_INCLUDED
