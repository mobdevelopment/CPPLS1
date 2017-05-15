#ifndef GAME_NODES_PLACEHOLDER_HEADER_INCLUDED
#define GAME_NODES_PLACEHOLDER_HEADER_INCLUDED

#include "node.h"
#include "type.h"

namespace game
{
namespace nodes
{
	class Placeholder :
		public Node<HorizontalCorridor, Type::PLACEHOLDER>
	{
	}; // class Placeholder
} // namespace nodes
} // namespace game

#endif // #ifndef GAME_NODES_PLACEHOLDER_HEADER_INCLUDED
