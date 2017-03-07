#ifndef GAME_NODES_CORRIDOR_HEADER_INCLUDED
#define GAME_NODES_CORRIDOR_HEADER_INCLUDED

#include "node.h"
#include "type.h"

#include "room.h"

namespace game
{
namespace nodes
{
	class Corridor
	{
	public:
		Room* room1;
		Room* room2;

		bool collapsed = false;

		virtual ~Corridor() noexcept = 0;

		Room* GetOther(const Room* const room) const;

		virtual unsigned int GetWeight() const = 0;
	}; // class Corridor
} // namespace nodes
} // namespace game

#endif // #ifndef GAME_NODES_CORRIDOR_HEADER_INCLUDED
