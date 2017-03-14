#include "horizontalcorridor.h"
#include "verticalcorridor.h"
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

std::string StairsDown::GetDescription() const
{
	std::stringstream stream;

	stream << "It's a stair going downstairs";

	return stream.str();
}