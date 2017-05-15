#include "verticalcorridor.h"

using namespace game::nodes;

unsigned int VerticalCorridor::GetWeight() const
{
	return room1->GetWeight() + room2->GetWeight();
}

Space* VerticalCorridor::GetNorthRoom()
{
	return room1;
}

Space* VerticalCorridor::GetSouthRoom()
{
	return room2;
}

void VerticalCorridor::SetNorthRoom(Space* const room)
{
	room1 = room;
}

void VerticalCorridor::SetSouthRoom(Space* const room)
{
	room2 = room;
}
