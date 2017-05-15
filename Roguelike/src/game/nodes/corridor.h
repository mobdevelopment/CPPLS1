#ifndef GAME_NODES_CORRIDOR_HEADER_INCLUDED
#define GAME_NODES_CORRIDOR_HEADER_INCLUDED

#include "node.h"
#include "type.h"

namespace game
{
namespace nodes
{
	class Space;

	class Corridor
	{
	public:
		Space* room1;
		Space* room2;

		bool collapsed = false;

		virtual ~Corridor() noexcept = 0;

		Space* GetOther(const Space* const room) const;

		virtual unsigned int GetWeight() const = 0;
	}; // class Corridor
} // namespace nodes
} // namespace game

#endif // #ifndef GAME_NODES_CORRIDOR_HEADER_INCLUDED
