#include "space.h"

using namespace game::nodes;

std::vector<Corridor*> Space::GetConnectedCorridors() const
{
	std::vector<Corridor*> corridors;

	if (northCorridor != nullptr && !northCorridor->collapsed)
		corridors.push_back(northCorridor);
	if (eastCorridor != nullptr && !eastCorridor->collapsed)
		corridors.push_back(eastCorridor);
	if (southCorridor != nullptr && !southCorridor->collapsed)
		corridors.push_back(southCorridor);
	if (westCorridor != nullptr && !westCorridor->collapsed)
		corridors.push_back(westCorridor);

	return corridors;
}

std::vector<Space*> Space::GetConnectedRooms() const
{
	std::vector<Space*> rooms;

	if (northCorridor != nullptr && northCorridor->GetNorthRoom() != nullptr && !northCorridor->collapsed)
		rooms.push_back(northCorridor->GetNorthRoom());
	if (eastCorridor != nullptr && eastCorridor->GetEastRoom() != nullptr && !eastCorridor->collapsed)
		rooms.push_back(eastCorridor->GetEastRoom());
	if (southCorridor != nullptr && southCorridor->GetSouthRoom() != nullptr && !southCorridor->collapsed)
		rooms.push_back(southCorridor->GetSouthRoom());
	if (westCorridor != nullptr && westCorridor->GetWestRoom() != nullptr && !westCorridor->collapsed)
		rooms.push_back(westCorridor->GetWestRoom());

	return rooms;
}