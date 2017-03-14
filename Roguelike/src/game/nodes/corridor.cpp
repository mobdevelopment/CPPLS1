#include "corridor.h"

using namespace game::nodes;

Corridor::~Corridor() noexcept
{
}

Space* Corridor::GetOther(const Space* const room) const
{
	if (room1 == room)
		return room2;
	else if (room2 == room)
		return room1;
	return nullptr;
}
