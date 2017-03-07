#include "horizontalcorridor.h"

using namespace game::nodes;

unsigned int HorizontalCorridor::GetWeight() const
{
	return room1->GetWeight() + room2->GetWeight();
}

Room* HorizontalCorridor::GetEastRoom()
{
	return room1;
}

Room* HorizontalCorridor::GetWestRoom()
{
	return room2;
}

void HorizontalCorridor::SetEastRoom(Room* const room)
{
	room1 = room;
}

void HorizontalCorridor::SetWestRoom(Room* const room)
{
	room2 = room;
}
