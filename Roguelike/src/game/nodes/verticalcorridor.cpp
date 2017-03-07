#include "verticalcorridor.h"

using namespace game::nodes;

unsigned int VerticalCorridor::GetWeight() const
{
	return room1->GetWeight() + room2->GetWeight();
}

Room* VerticalCorridor::GetNorthRoom()
{
	return room1;
}

Room* VerticalCorridor::GetSouthRoom()
{
	return room2;
}

void VerticalCorridor::SetNorthRoom(Room* const room)
{
	room1 = room;
}

void VerticalCorridor::SetSouthRoom(Room* const room)
{
	room2 = room;
}
