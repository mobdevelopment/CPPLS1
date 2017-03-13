#include "stairsdown.h"

using namespace game::nodes;

unsigned int StairsDown::GetWeight() const
{
	return 1;
}

StairsUp* StairsDown::GetBottomRoom() const
{
	return bottomRoom;
}

void StairsDown::SetBottomRoom(StairsUp* const room)
{
	bottomRoom = room;
}