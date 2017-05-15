#include "horizontalcorridor.h"

using namespace game::nodes;

unsigned int HorizontalCorridor::GetWeight() const
{
	return room1->GetWeight() + room2->GetWeight();
}

Space* HorizontalCorridor::GetEastRoom()
{
	return room1;
}

Space* HorizontalCorridor::GetWestRoom()
{
	return room2;
}

void HorizontalCorridor::SetEastRoom(Space* const room)
{
	room1 = room;
}

void HorizontalCorridor::SetWestRoom(Space* const room)
{
	room2 = room;
}