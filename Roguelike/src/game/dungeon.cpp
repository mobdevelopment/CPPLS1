#include "dungeon.h"

using namespace game;

Dungeon::Dungeon() noexcept
{
	Clear();
}

Dungeon::iterator Dungeon::begin()
{
	return layers.begin();
}

Dungeon::const_iterator Dungeon::begin() const
{
	return layers.begin();
}

Dungeon::const_iterator Dungeon::cbegin() const
{
	return layers.cbegin();
}

Dungeon::iterator Dungeon::end()
{
	return layers.end();
}

Dungeon::const_iterator Dungeon::end() const
{
	return layers.end();
}

Dungeon::const_iterator Dungeon::cend() const
{
	return layers.cend();
}

DungeonLayer& Dungeon::operator[](const unsigned int index) noexcept
{
	return layers[index];
}

const DungeonLayer& Dungeon::operator[](const unsigned int index) const noexcept
{
	return layers[index];
}

void Dungeon::Clear() noexcept
{
	seed = 0;
	layerCount = 0;
	roomsWidth = 0;
	roomsHeight = 0;
	layers.clear();
}

void Dungeon::Fill(const unsigned int layerCount, const unsigned int width, const unsigned int height)
{
	// Validate input.
	if (layerCount == 0 || width == 0 || height == 0)
		throw std::system_error(Error::DUNGEON_PARAMETER_ZERO_VALUE);

	this->layerCount = layerCount;
	roomsWidth = width;
	roomsHeight = height;

	auto totalWidth = GetTotalWidth();
	auto totalHeight = GetTotalHeight();

	for (unsigned int z = 0; z < layerCount; z++)
	{
		layers.emplace_back();
		layers[z].SetWidth(totalWidth);
		layers[z].SetHeight(totalHeight);

		// Construct the rooms and corridors first.
		for (unsigned int y = 0; y < totalHeight; y++)
		{
			// Uneven rows only have vertical corridors every even node.
			if (y % 2 != 0)
			{
				for (unsigned int x = 0; x < totalWidth; x++)
				{
					if (x % 2 == 0)
						layers[z][y].SetNode(x, new nodes::VerticalCorridor());
				}
			}
			else
			{
				for (unsigned int x = 0; x < totalWidth; x++)
				{
					// Even is a room. Uneven a corridor.
					if (x % 2 == 0)
						layers[z][y].SetNode(x, new nodes::Room());
					else
						layers[z][y].SetNode(x, new nodes::HorizontalCorridor());
				}
			}
		}

		// Now couple them together.
		for (unsigned int y = 0; y < totalHeight; y++)
		{
			// Uneven rows only have vertical corridors every even node.
			if (y % 2 != 0)
			{
				for (unsigned int x = 0; x < totalWidth; x++)
				{
					if (x % 2 == 0)
					{
						auto corridor = static_cast<nodes::VerticalCorridor*>(layers[z][y][x]);

						corridor->SetNorthRoom((nodes::Room*)layers[z][y + 1][x]);
						corridor->SetSouthRoom((nodes::Room*)layers[z][y - 1][x]);
					}
				}
			}
			else
			{
				for (unsigned int x = 0; x < totalWidth; x++)
				{
					// Corridors are at every uneven node and rooms at the even ones.
					if (x % 2 != 0)
					{
						auto corridor = static_cast<nodes::HorizontalCorridor*>(layers[z][y][x]);

						corridor->SetEastRoom((nodes::Room*)layers[z][y][x + 1]);
						corridor->SetWestRoom((nodes::Room*)layers[z][y][x - 1]);

						corridor = corridor;
					}
					else
					{
						auto room = static_cast<nodes::Room*>(layers[z][y][x]);

						// No room to the north on the top row.
						if (y != totalHeight - 1)
							room->northCorridor = static_cast<nodes::VerticalCorridor*>(layers[z][y + 1][x]);

						// No room to the south on the first row.
						if (y != 0)
							room->southCorridor = static_cast<nodes::VerticalCorridor*>(layers[z][y - 1][x]);

						// No room to the east on the last node.
						if (x != totalWidth - 1)
							room->eastCorridor = static_cast<nodes::HorizontalCorridor*>(layers[z][y][x + 1]);

						// No room to the west on the first node.
						if (x != 0)
							room->westCorridor = static_cast<nodes::HorizontalCorridor*>(layers[z][y][x - 1]);

						room = room;
					}
				}
			}
		}
	}
}

void Dungeon::Randomize(const unsigned int layerCount, const unsigned int width, const unsigned int height)
{
	Randomize(layerCount, width, height, std::random_device()());
}

void Dungeon::Randomize(const unsigned int layerCount, const unsigned int width, const unsigned int height, const unsigned int seed)
{
	// Validate input.
	if (layerCount == 0 || width == 0 || height == 0)
		throw std::system_error(Error::DUNGEON_PARAMETER_ZERO_VALUE);

	Clear();

	this->seed = seed;

	// Dungeon layers are using a left handed coordinate system sort of like this.
	// This dungeon layer is 3x3.
	//
	// 4 |*-N-*
	// 3 || | |
	// 2 |*-*-*
	// 1 || | |
	// 0 |*-*-*
	//   -------
	//    01234
	// Room N = x=2,y=4 or 2,4

	// Construct the layers and fill them with empty rooms.
	Fill(layerCount, width, height);

	auto totalWidth = GetTotalWidth();
	auto totalHeight = GetTotalHeight();

	// Rng stuff.
	std::default_random_engine generator;
	generator.seed(seed);
	std::uniform_int_distribution<int> xDist(0, totalWidth - 2);
	std::uniform_int_distribution<int> yDist(0, totalHeight - 2);
	std::uniform_int_distribution<int> coinDist(0, 1);

	for (unsigned int z = 0; z < layerCount; z++)
	{
		auto& layer = layers[z];

		// Construct a minimal spanning tree to see which corridors we can not remove.
		// TODO: Use a set instead for performance.
		auto mstCorridors = layer.GetMinimalSpanningTree(seed);

		// TODO: Something better than a random number.
		// Remove a number of corridors.
		for (int i = 0; i < 1000; i++)
		{
			// Get a random corridor location. Must be an odd and an even number because two even nodes are rooms and two odd numbers are nothing.
			// TODO: Fix that it won't get the last row or column...
			unsigned int x = xDist(generator);
			unsigned int y = yDist(generator);

			if (x % 2 == 0)
			{
				if (y % 2 == 0)
				{
					if (coinDist(generator))
						x += 1;
					else
						y += 1;
				}
			}
			else if (y % 2 != 0)
			{
				if (coinDist(generator))
					x -= 1;
				else
					y -= 1;
			}

			// Check if the corridor wasn't already removed.
			if (layer[y][x] != nullptr)
			{
				// Delete the references to the corridors from the rooms it is connected to.
				if (y % 2 == 0)
				{
					auto hCorridor = static_cast<nodes::HorizontalCorridor*>(layer[y][x]);

					// Check if the corridor isn't in the minimal spanning tree.
					if (std::find(mstCorridors.begin(), mstCorridors.end(), hCorridor) != mstCorridors.end())
						continue;

					hCorridor->GetEastRoom()->westCorridor = nullptr;
					hCorridor->GetWestRoom()->eastCorridor = nullptr;
				}
				else
				{
					auto vCorridor = static_cast<nodes::VerticalCorridor*>(layer[y][x]);

					// Check if the corridor isn't in the minimal spanning tree.
					if (std::find(mstCorridors.begin(), mstCorridors.end(), vCorridor) != mstCorridors.end())
						continue;

					vCorridor->GetNorthRoom()->southCorridor = nullptr;
					vCorridor->GetSouthRoom()->northCorridor = nullptr;
				}

				// Delete the corridor.
				layer[y].SetNode(x, nullptr);
			}
		}
	}

	nodes::StairsUp* prevStairUp = nullptr;

	for (unsigned int z = 0; z < layerCount; z++)
	{
		auto& layer = layers[z];

		if (z > 0)
		{
			unsigned int x = xDist(generator);
			unsigned int y = yDist(generator);
			if (x % 2 != 0) x++;
			if (y % 2 != 0) y++;
			auto node = static_cast<nodes::Room*>(layer[y][x]);

			auto stairDown = new nodes::StairsDown();

			if (node->eastCorridor != nullptr) {
				node->eastCorridor->SetWestRoom(stairDown);
				stairDown->eastCorridor = node->eastCorridor;
			}
			if (node->westCorridor != nullptr) {
				node->westCorridor->SetEastRoom(stairDown);
				stairDown->westCorridor = node->westCorridor;
			}
			if (node->northCorridor != nullptr) {
				node->northCorridor->SetSouthRoom(stairDown);
				stairDown->northCorridor = node->northCorridor;
			}
			if (node->southCorridor != nullptr) {
				node->southCorridor->SetNorthRoom(stairDown);
				stairDown->southCorridor = node->southCorridor;
			}

			layer[y].SetNode(x, stairDown);
			if (prevStairUp != nullptr)
			{
				stairDown->SetBottomRoom(prevStairUp);
				prevStairUp->SetTopRoom(stairDown);
			}
		}

		if (z < layerCount - 1)
		{
			unsigned int x = xDist(generator);
			unsigned int y = yDist(generator);

			if (x % 2 != 0) x++;
			if (y % 2 != 0) y++;

			auto node = static_cast<nodes::Room*>(layer[y][x]);
			//auto node = static_cast<nodes::Room*>(layer[0][0]);

			auto stairUp = new nodes::StairsUp();

			if (node->eastCorridor != nullptr) {
				node->eastCorridor->SetWestRoom(stairUp);
				stairUp->eastCorridor = node->eastCorridor;
			}
			if (node->westCorridor != nullptr) {
				node->westCorridor->SetEastRoom(stairUp);
				stairUp->westCorridor = node->westCorridor;
			}
			if (node->northCorridor != nullptr) {
				node->northCorridor->SetSouthRoom(stairUp);
				stairUp->northCorridor = node->northCorridor;
			}
			if (node->southCorridor != nullptr) {
				node->southCorridor->SetNorthRoom(stairUp);
				stairUp->southCorridor = node->southCorridor;
			}

			layer[y].SetNode(x, stairUp);
			prevStairUp = stairUp;
		}
	}
}

Dungeon::LayersContainer& Dungeon::GetLayers() noexcept
{
	return layers;
}

const Dungeon::LayersContainer& Dungeon::GetLayers() const noexcept
{
	return layers;
}

unsigned int Dungeon::GetRoomsWidth() const
{
	return roomsWidth;
}

unsigned int Dungeon::GetRoomsHeight() const
{
	return roomsHeight;
}

unsigned int Dungeon::GetTotalWidth() const
{
	return roomsWidth * 2 - 1;
}

unsigned int Dungeon::GetTotalHeight() const
{
	return roomsHeight * 2 - 1;
}
