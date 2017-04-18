#include "dungeonlayer.h"

using namespace game;

DungeonLayer::DungeonLayer() noexcept :
	width(0),
	height(0)
{
}

DungeonLayer::iterator DungeonLayer::begin()
{
	return rows.begin();
}

DungeonLayer::const_iterator DungeonLayer::begin() const
{
	return rows.begin();
}

DungeonLayer::const_iterator DungeonLayer::cbegin() const
{
	return rows.cbegin();
}

DungeonLayer::iterator DungeonLayer::end()
{
	return rows.end();
}

DungeonLayer::const_iterator DungeonLayer::end() const
{
	return rows.end();
}

DungeonLayer::const_iterator DungeonLayer::cend() const
{
	return rows.cend();
}

DungeonRow& DungeonLayer::operator[](const unsigned int index) noexcept
{
	return rows[index];
}

const DungeonRow& DungeonLayer::operator[](const unsigned int index) const noexcept
{
	return rows[index];
}

unsigned int DungeonLayer::GetWidth() const noexcept
{
	return width;
}

unsigned int DungeonLayer::GetHeight() const noexcept
{
	return height;
}

unsigned int DungeonLayer::GetSurfaceArea() const noexcept
{
	return width * height;
}

DungeonLayer::RowsContainer& DungeonLayer::GetRows() noexcept
{
	return rows;
}

const DungeonLayer::RowsContainer& DungeonLayer::GetRows() const noexcept
{
	return rows;
}

nodes::Room* DungeonLayer::GetRandomRoom() const noexcept
{
	// Rng stuff.
	std::default_random_engine generator;
	generator.seed(std::random_device()());
	std::uniform_int_distribution<int> xDist(0, width - 1);
	std::uniform_int_distribution<int> yDist(0, height - 1);

	// Get a random room node/vertex location. Must be an even number because uneven nodes are corridors.
	nodes::Room* room = nullptr;

	while (room == nullptr)
	{
		unsigned int x = xDist(generator) * 2 % (width + 1);
		unsigned int y = yDist(generator) * 2 % (height + 1);

		room = (nodes::Room*)rows[y][x];
	}

	return room;
}

void DungeonLayer::SetWidth(const unsigned int width)
{
	for (auto& row : rows)
	{
		row.SetWidth(width);
	}
	this->width = width;
}

void DungeonLayer::SetHeight(const unsigned int height)
{
	if (height == this->height)
		return;

	rows.resize(height);

	if (height > this->height)
	{
		unsigned int index = this->height;
		if (index > 0)
			index--;

		for (unsigned int i = index; i < height; i++)
		{
			rows[i].SetWidth(width);
		}
	}

	this->height = height;
}

bool DungeonLayer::IsEverythingAccessible() const
{
	// With Prim's minimum cost tree algorithm.

	const auto* const startingRoom = GetRandomRoom();

	std::unordered_set<const nodes::Space*> unvisitedRooms;
	std::unordered_set<const nodes::Space*> visitedRooms;

	// Fill the unvisited vertices.
	for (const auto& row : rows)
	{
		for (const auto* const room : row.GetRooms())
		{
			unvisitedRooms.insert(room);
		}
	}

	// Move the startingvertex from the unvisited to the visited.
	unvisitedRooms.erase(startingRoom);
	visitedRooms.insert(startingRoom);

	while (true)
	{
		const nodes::Space*	cheapestRoom = nullptr;
		unsigned int		cheapestRoomWeight = std::numeric_limits<unsigned int>::max();

		// Get the node/vertex with the cheapest edge to an unvisited node/vertex.
		for (const nodes::Space* const visitedRoom : visitedRooms)
		{
			auto connectedRooms = visitedRoom->GetConnectedRooms();

			for (const nodes::Space* const connectedRoom : connectedRooms)
			{
				// Check if we haven't already visited this room.
				if (visitedRooms.count(connectedRoom) != 0)
					continue;

				auto connectedRoomWeight = connectedRoom->GetWeight();
				if (connectedRoomWeight < cheapestRoomWeight)
				{
					cheapestRoom = connectedRoom;
					cheapestRoomWeight = connectedRoomWeight;
				}
			}
		}

		// If we couldn't find a connected room and we still have rooms to visit we can not access everything.
		// If we have no more rooms to visit we can return true.
		if (cheapestRoom != nullptr)
		{
			unvisitedRooms.erase(cheapestRoom);
			visitedRooms.insert(cheapestRoom);
		}
		else
		{
			if (!unvisitedRooms.empty())
				return false;
		}

		if (unvisitedRooms.empty())
			break;
	}

	return true;
}

std::vector<nodes::Corridor*> DungeonLayer::GetMinimalSpanningTree(const int seed) const
{
	// With Prim's minimum cost tree algorithm.

	// Rng stuff
	std::default_random_engine generator;
	//generator.seed(std::random_device()());
	generator.seed(seed);

	const auto* const startingRoom = GetRandomRoom();

	std::unordered_set<const nodes::Space*>	unvisitedRooms;
	std::unordered_set<const nodes::Space*>	visitedRooms;
	std::vector<nodes::Corridor*>			corridors;

	// Fill the unvisited rooms.
	for (const auto& row : rows)
	{
		for (const auto* const room : row.GetRooms())
		{
			unvisitedRooms.insert(room);
		}
	}

	// Move the starting room from the unvisited to the visited.
	unvisitedRooms.erase(startingRoom);
	visitedRooms.insert(startingRoom);

	while (true)
	{
		// Get the corridors with the least weight to an unvisited room.
		unsigned int					cheapestCorridorsWeight = std::numeric_limits<unsigned int>::max();
		std::vector<nodes::Corridor*>	cheapestCorridors;

		for (const nodes::Space* const visitedRoom : visitedRooms)
		{
			const auto connectedCorridors = visitedRoom->GetConnectedCorridors();

			for (nodes::Corridor* const connectedCorridor : connectedCorridors)
			{
				const nodes::Space* const connectedRoom = connectedCorridor->GetOther(visitedRoom);

				// Check if we haven't already visited the room on the other side of the corridor.
				if (visitedRooms.count(connectedRoom) != 0)
					continue;

				auto connectedCorridorWeight = connectedCorridor->GetWeight();
				if (connectedCorridorWeight == cheapestCorridorsWeight)
				{
					cheapestCorridors.push_back(connectedCorridor);
				}
				else if (connectedCorridorWeight < cheapestCorridorsWeight)
				{
					cheapestCorridorsWeight = connectedCorridorWeight;
					cheapestCorridors.clear();
					cheapestCorridors.push_back(connectedCorridor);
				}
			}
		}

		if (cheapestCorridors.size() != 0)
		{
			// Get a random corridor from the cheapest ones.
			std::uniform_int_distribution<int> dist(0, cheapestCorridors.size() - 1);

			auto cheapestCorridor = cheapestCorridors[dist(generator)];
			const nodes::Space* cheapestRoom;
			if (visitedRooms.count(cheapestCorridor->room1) == 0)
				cheapestRoom = cheapestCorridor->room1;
			else
				cheapestRoom = cheapestCorridor->room2;

			unvisitedRooms.erase(cheapestRoom);
			visitedRooms.insert(cheapestRoom);
			corridors.push_back(cheapestCorridor);
		}
		else
		{
			if (!unvisitedRooms.empty())
				throw std::runtime_error("No minimal spanning tree possible.");
		}

		if (unvisitedRooms.empty())
			break;
	}

	return corridors;
}
