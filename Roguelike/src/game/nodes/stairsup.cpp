#include "stairsup.h"

using namespace game::nodes;

unsigned int StairsUp::GetWeight() const
{
	return 1;
}

StairsDown* StairsUp::GetTopRoom()
{
	return topRoom;
}

void StairsUp::SetTopRoom(StairsDown* const room)
{
	topRoom = room;
}