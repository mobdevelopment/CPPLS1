#include "horizontalcorridor.h"
#include "verticalcorridor.h"
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

std::string StairsUp::GetDescription() const
{
	std::stringstream stream;

	stream << "It's a stair going upstairs";

	return stream.str();
}